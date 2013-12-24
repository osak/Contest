//Name: Roping the Field
//Level: 4
//Category: 幾何,Geometry,動的計画法,DP
//Note:

/**
 * 対角線のうち円と交差しないものは適当に求める。
 *
 * 使える対角線を列挙したあとで、交差しないようにして配置できる個数の最大値を求める。
 * [i, j]の範囲にある頂点のみを使うとすると、i番の頂点からは
 * ・k番の頂点へ対角線を引き、[i, k-1]と[k, j]の区間で対角線を引く
 * ・対角線を引かず、[i+1, j]の区間で対角線を引く
 * のどちらかになる。
 * これはDPになる。
 *
 * オーダーはO(N^2G + N^3)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <complex> 

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

typedef complex<double> P;
static const double PI = acos(-1.0);
static const double EPS = 1e-9;

inline double dot(const P& a, const P& b) { return a.real()*b.real() + a.imag()*b.imag(); }
inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

struct line/*{{{*/
{
  P a, b;
  line() {}
  line(const P& p, const P& q) : a(p), b(q) {}

  inline double distance(const P& p) const
  {
    return abs(cross(p - a, b - a)) / abs(b - a);
  }
};/*}}}*/

struct circle/*{{{*/
{
  P o;
  double r;
  circle() {}
  circle(const P& p, double x) : o(p), r(x) {}

  inline bool contains(const P &p) const {
      return abs(p - o) <= r+EPS;
  }

  inline bool intersects(const line& ln) const
  {
    return abs(ln.distance(o)) <= r+EPS;
  }
};/*}}}*/

vector<int> ropes[150];
int dp[150][150];
int calc(int left, int right) {
    if(left == right) return 0;
    int &res = dp[left][right];
    if(res != -1) return res;

    res = 0;
    TIMES(i, (int)ropes[left].size()) {
        const int nr = ropes[left][i];
        if(nr < left || nr > right) continue;
        res = max(res, calc(left, nr-1) + calc(nr, right) + 1);
    }
    res = max(res, calc(left+1, right));
    return res;
}

bool solve() {
    int N, G, R;
    if(scanf("%d %d %d", &N, &G, &R) == EOF) return false;
    if(!N && !G && !R) return false;

    static P points[150];
    static circle circles[100];
    TIMES(i, N) {
        int x, y;
        scanf("%d %d", &x, &y);
        points[i] = P(x, y);
        ropes[i].clear();
    }
    TIMES(i, G) {
        int x, y;
        scanf("%d %d", &x, &y);
        circles[i] = circle(P(x, y), R);
    }
    TIMES(i, N) {
        TIMES(j, i) {
            if(i == (j+1) % N || j == (i+1) % N) continue;
            bool ok = true;
            line l(points[i], points[j]);
            TIMES(k, G) {
                if(   circles[k].contains(points[i])
                   || circles[k].contains(points[j]))
                {
                    ok = false;
                    break;
                }
                if(circles[k].intersects(l)) {
                    const double flg = 
                        dot(circles[k].o - points[j], points[j] - points[i])
                        * dot(circles[k].o - points[i], points[j] - points[i]);
                    if(flg <= 0) {
                        ok = false;
                        break;
                    }
                }
            }
            if(ok) {
                //printf("%d %d\n", i, j);
                ropes[i].push_back(j);
                ropes[j].push_back(i);
            }
        }
    }
    TIMES(i, N) {
        TIMES(j, N) {
            dp[i][j] = -1;
        }
    }
    const int ans = calc(0, N-1);
    printf("%d\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
