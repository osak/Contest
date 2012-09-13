// vim:fdm=marker:
//matrix {{{
#include <vector>
typedef vector<ULL> Row;
typedef vector<Row> Matrix;

// Codeforces 222E Decoding Genome
// 行列のかけ算
Matrix operator*(const Matrix &a, const Matrix &b) {
    const int A = a.size();
    const int B = b[0].size();
    const int C = b.size();
    Matrix res(A, Row(B));
    for(int i = 0; i < A; ++i) {
        for(int j = 0; j < B; ++j) {
            ULL acc = 0;
            for(int k = 0; k < C; ++k) {
                acc += a[i][k] * b[k][j];
                //If need mod
                //acc %= MOD;
            }
            res[i][j] = acc;
        }
    }
    return res;
}

// Codeforces 222E Decoding Genome
// 正方行列matの0乗，1乗，2乗，4乗，……，2^(cnt)乗を作る．
vector<Matrix>& gen_base(Matrix mat, int cnt, vector<Matrix> &out) {
    const int N = mat.size();
    out.clear();
    Matrix ident(N, Row(N, 0));
    for(int i = 0; i < N; ++i) ident[i][i] = 1;
    out.push_back(ident);
    for(int i = 1; i <= cnt; ++i) {
        out.push_back(mat);
        mat = mat * mat;
    }
    return out;
}

// Codeforces 222E Decoding Genome
// gen_base で作った行列からx乗を求める．
Matrix mat_pow(const vector<Matrix> &base, int x) {
    const int N = base.size();
    Matrix res(base[0]);
    for(int i = 1; i < N && x > 0; ++i, x>>=1) {
        if(x&1) res = res * base[i];
    }
    return res;
}
//}}}

struct mod/*{{{*/
{
  int m;
  vector<int> tbl;
  mod(int a) : m(a), tbl(m+1)
  {
    for (int x = 1; x < m; x++) {
      tbl[x] = pow(x, a-2);
    }
  }
  int pow(int x, int e)
  {
    if (e == 0) {
      return 1;
    } else if (e & 1) {
      return (x * pow(x, e-1))%m;
    } else {
      const int y = pow(x, e>>1);
      return (y*y)%m;
    }
  }
  int operator()(int x) const { return ((x%m)+m)%m; }
  int inv(int x) const { return tbl[x]; }
};/*}}}*/

long long gcd(long long a, long long b)/*{{{*/
{
  if (a < b) {
    swap(a, b);
  }
  long long r;
  while ((r = a % b) != 0LL) {
    a = b;
    b = r;
  }
  return b;
}/*}}}*/

struct ratio/*{{{*/
{
  long long n, d;
  ratio() : n(0), d(1) {}
  ratio(long long a) : n(a), d(1) {}
  ratio(long long a, long long b) : n(a), d(b) { normalize(); }

  void normalize()
  {
    if (n == 0) {
      d = 1;
    } else {
      const long long g = gcd(n, d);
      n /= g;
      d /= g;
      if (d < 0) {
        n = -n;
        d = -d;
      }
    }
  }

  ratio inverse() const { return ratio(d, n); }

  bool operator==(const ratio& r) const { return n == r.n && d == r.d; }
  bool operator==(int x) const { return d == 1 && n == x; }
  ratio operator-() const { return ratio(-n, d); }

  ratio& operator-=(const ratio& r)
  {
    const long long dd = d * r.d;
    const long long nn = n*r.d - r.n*d;
    d = dd;
    n = nn;
    normalize();
    return *this;
  }
  ratio operator*(const ratio& r) const { return ratio(n * r.n, d * r.d); }
};/*}}}*/

// ax = b を解く。解 x は b に入る。
// N < M のときは 0 = 0 みたいな式を追加して N == M にする。
template <class T>
bool gaussian_elimination(vector<vector<T> >& a, vector<T>& b, const mod& MOD)/*{{{*/
{
  const int N = a.size();
  const int M = a[0].size();
  // assert(N >= M)

  for (int i = 0, p = 0; i < M; i++, p++) {
    int q;
    for (q = p; q < N && a[q][i] == 0; q++);
    if (q == N) {
      --p;
      continue;
    }
    swap(a[i], a[q]);
    swap(b[i], b[q]);

    // const T r = 1.0/a[i][i];
    // const T r = a[i][i].inverse();
    const T r = MOD.inv(a[i][i]);
    for (int k = i; k < M; k++) {
      a[i][k] = MOD(a[i][k] * r);
    }
    b[i] = MOD(b[i] * r);

    for (int j = 0; j < N; j++) {
      if (j == i) {
        continue;
      }
      const T t = a[j][i];
      for (int k = i; k < M; k++) {
        a[j][k] = MOD(a[j][k] - t * a[i][k]);
      }
      b[j] = MOD(b[j] - t * b[i]);
    }
  }

  for (int i = 0; i < M; i++) {
    if (a[i][i] == 0 && b[i] != 0) {
      // no solution
      return false;
    }
  }
  return true;
}/*}}}*/

