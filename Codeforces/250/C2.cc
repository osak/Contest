//Name: The Child and Polygon
//Level: 4
//Category: 幾何,Geometry,動的計画法,DP
//Note:

/**
 * 多角形の頂点を順に0, 1, 2, ... N-1として、iからj番目までの頂点だけで構成される多角形の分割パターン数をdp[i][j]とする。
 * このとき、求めるのはdp[0][N-1]である。
 * ここで、辺(i, j)を使った三角形を考えると、もうひとつの頂点kは、頂点iと頂点jから見えていて、かつ(i,k)と(j,k)はどちらも元の多角形の内部を通るような物でなければならない。
 * また、縮退した三角形になってはならない。
 * このように分割すると、残りはdp[i][k]とdp[k][j]になり、これらの分割パターン数の積だけ分割が可能である。
 * したがって、
 *   dp[i][j] = ∑ dp[i][k] * dp[k][j]
 * である。
 *
 * オーダーはO(N^3)。
 */
#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef complex<double> P;

const LL MOD = 1000000007;
const double EPS = 1e-8;

inline double dot(const P& a, const P& b) { return a.real()*b.real() + a.imag()*b.imag(); }
inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

int ccw(const P& a, P b, P c)
{
  b -= a;
  c -= a;
  if (cross(b, c) > EPS) { // ccw
    return +1;
  } else if (cross(b, c) < -EPS) { // cw
    return -1;
  } else if (dot(b, c) < -EPS) { // c-a-b or b-a-c
    return +2;
  } else if (dot(b, b) + EPS < dot(c, c)) { // a-b-c
    return -2;
  } else { // a-c-b
    return 0;
  }
}

struct segment/*{{{*/
{
  P a, b;
  segment() {}
  segment(const P& x, const P& y) : a(x), b(y) {}

  // AOJ 2402 Milkey Way
  inline bool intersects(const segment& seg) const
  {
    return ccw(a, b, seg.a) * ccw(a, b, seg.b) <= 0
      && ccw(seg.a, seg.b, a) * ccw(seg.a, seg.b, b) <= 0;
  }
};/*}}}*/

inline double area(const P &a, const P &b, const P &c) {
    return abs(cross(b-a, c-a) / 2);
}

bool in_polygon(const vector<int> &polygon, const vector<P> &vert, const P &p) {
    const int N = polygon.size();
    segment seg(p, P(2e7, p.imag()+0.1));
    int cnt = 0;
    for(int i = 0; i < N; ++i) {
        const int ni = (i+1) % N;
        segment edge(vert[polygon[i]], vert[polygon[ni]]);
        if(seg.intersects(edge)) ++cnt;
        if(ccw(edge.a, p, edge.b) == -2) return true;
    }
    return cnt % 2 == 1;
}

bool visible(const vector<int> &polygon, int a, int b, const vector<P> &vert) {
    const int N = polygon.size();
    if(abs(a-b) == 1 || abs(a-b) == N-1) return true; // neighbor in polygon

    segment seg(vert[polygon[a]], vert[polygon[b]]);
    const P v = seg.b - seg.a;
    if(!in_polygon(polygon, vert, seg.a + v/abs(v)*0.1) || !in_polygon(polygon, vert, seg.b - v/abs(v)*0.1)) return false;

    for(int i = 0; i < N; ++i) {
        const int nv = (i+1) % N;
        if(i == a || i == b) continue;
        if(nv == a || nv == b) {
        } else {
            segment edge(vert[polygon[i]], vert[polygon[nv]]);
            if(seg.intersects(edge)) return false;
        }
        const int ccw_val = ccw(seg.a, vert[polygon[i]], seg.b);
        //cout << vert[polygon[i]] << ' ' << ccw_val << endl;
        // point is on seg
        if(ccw_val == -2) { // a-mid-b
            return false;
        }
    }
    return true;
}

int vis_memo[210][210];
bool visible_memo(int a, int b) {
    return vis_memo[a][b];
}

ostream& operator <<(ostream &os, const vector<int> &v) {
    for(int val : v) {
        os << val << ' ';
    }
    return os;
}

LL memo[210][210];
LL calc(int a, int b) {
    const int N = b - a + 1;
    LL &res = memo[a][b];
    if(res != -1) {
        return res;
    }

    if(N == 3 || N == 2) return res = 1;
    if(N < 3) return res = 0; // ?
    
    res = 0;
    for(int i = a+1; i < b; ++i) {
        if(visible_memo(a, i) && visible_memo(b, i)) {
            res += calc(a, i) * calc(i, b);
            res %= MOD;
        }
    }
    return res;
}

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    vector<P> vert;
    vector<int> polygon;

    for(int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        vert.push_back(P(x, y));
        polygon.push_back(i);
    }
    fill_n((LL*)memo, sizeof(memo) / sizeof(LL), -1);
    fill_n((int*)vis_memo, sizeof(vis_memo) / sizeof(int), -1);
    for(int i = 0; i < N; ++i) {
        for(int j = i+1; j < N; ++j) {
            vis_memo[j][i] = vis_memo[i][j] = visible(polygon, i, j, vert);
        }
    }
    cout << calc(0, N-1) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
