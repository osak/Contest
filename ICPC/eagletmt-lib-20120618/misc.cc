struct DisjointSet/*{{{*/
{
  vector<int> parent;

  int root(int x)
  {
    if (parent[x] < 0) {
      return x;
    } else {
      parent[x] = root(parent[x]);
      return parent[x];
    }
  }

  explicit DisjointSet(int n) : parent(n, -1) {}

  bool unite(int x, int y)
  {
    const int a = root(x);
    const int b = root(y);
    if (a != b) {
      if (parent[a] < parent[b]) {
        parent[a] += parent[b];
        parent[b] = a;
      } else {
        parent[b] += parent[a];
        parent[a] = b;
      }
      return true;
    } else {
      return false;
    }
  }

  bool find(int x, int y) { return root(x) == root(y); }
  int size(int x) { return -parent[root(x)]; }
};/*}}}*/

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

// 1-origin であることに注意．
// bit.add(1, 1); bit.add(2, 2);  bit.add(3, 3) とすると
// - tree[0] = 0
// - tree[1] = 1
// - tree[2] = 3
// - tree[3] = 6
// となる．
template <class T>
struct BinaryIndexedTree/*{{{*/
{
  T tree;
  const int size;
  BinaryIndexedTree(const T& t, int s) : tree(t), size(s) {}
  // i 番目までの要素の累積和
  int read(int i) const
  {
    int sum = 0;
    while (i > 0) {
      sum += tree[i];
      i -= i & -i;
    }
    return sum;
  }

  // i 番目の要素
  int read_single(int i) const
  {
    int sum = tree[i];
    if (i > 0) {
      const int z = i - (i & -i);
      --i;
      while (i != z) {
        sum -= tree[i];
        i -= (i & -i);
      }
    }
    return sum;
  }

  void add(int i, int v)
  {
    while (i <= size) {
      tree[i] += v;
      i += (i & -i);
    }
  }
};/*}}}*/

// POJ 3264 Balanced Lineup
template <class Compare>
struct SegmentTree/*{{{*/
{
  const vector<int>& cows;
  vector<int> indexes;
  Compare cmp;
  SegmentTree(const vector<int>& cs)
    : cows(cs), indexes(4*cs.size(), -1)
  {
    build(0, 0, cs.size());
  }

  void build(int idx, int left, int right)
  {
    if (left+1 == right) {
      indexes[idx] = left;
    } else {
      const int mid = (left + right)/2;
      build(2*idx+1, left, mid);
      build(2*idx+2, mid, right);
      // minimum in [left, right)
      if (cmp(cows[indexes[2*idx+1]], cows[indexes[2*idx+2]])) {
        indexes[idx] = indexes[2*idx+1];
      } else {
        indexes[idx] = indexes[2*idx+2];
      }
    }
  }

  inline int query_value(int left, int right) const { return cows[query_index(left, right)]; }

  inline int query_index(int left, int right) const { return query_index(left, right, 0, 0, cows.size()); }

  int query_index(int left, int right, int i, int a, int b) const
  {
    // [a, b) is the range of indexes[i]
    if (b <= left || right <= a) {
      // does not intersect
      return -1;
    } else if (left <= a && b <= right) {
      // contains
      return indexes[i];
    } else {
      const int m = (a+b)/2;
      const int l = query_index(left, right, 2*i+1, a, m);
      const int r = query_index(left, right, 2*i+2, m, b);
      if (l == -1) {
        return r;
      } else if (r == -1) {
        return l;
      } else {
        if (cmp(cows[l], cows[r])) {
          return l;
        } else {
          return r;
        }
      }
    }
  }
};/*}}}*/
