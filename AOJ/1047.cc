//Name: Crop Circle
//Level: 3
//Category: 幾何,Geometry,円,Circle
//Note:

/**
 * それぞれの円c1について、他の円c2との交点を取って、
 * 正の向きに数えてc1がc2の内側に入る直前で+1,出た直後で-1する。
 * これをすべてのc2に対して列挙し、カウンタが0の区間だけで長さを合計すればよい。
 * 円が完全に包含されているパターンに注意。
 *
 * オーダーはO(N^2)。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>
#include <cstdio>

using namespace std;

typedef complex<double> P;
const double PI = acos(-1);
const double EPS = 1e-9;

struct circle/*{{{*/
{
  P o;
  double r;
  circle() {}
  circle(const P& p, double x) : o(p), r(x) {}

  // POJ 1418 Viva Confetti
  // POJ 2149 Inherit the Spheres
  inline bool intersects(const circle& c) const
  {
    return !contains(c) && !c.contains(*this) && abs(o - c.o) <= r + c.r;
  }

  pair<P,P> intersection(const circle& c) const
  {
    // assert(intersects(c))
    const double d = abs(o - c.o);
    const double cos_ = (d*d + r*r - c.r*c.r) / (2*d);
    const double sin_ = sqrt(r*r - cos_*cos_);
    const P e = (c.o - o) / d;
    return make_pair(o + e*P(cos_, -sin_), o + e*P(cos_, sin_));
  }

  inline bool contains(const circle& c) const
  {
    return abs(o - c.o)+c.r <= r;
  }
};/*}}}*/

bool solve() {
    int N;
    cin >> N;
    if(!N) return false;

    vector<circle> cs;
    for(int i = 0; i < N; ++i) {
        double x, y, r;
        cin >> x >> y >> r;
        cs.push_back(circle(P(x, y), r));
    }
    double ans = 0;
    for(int i = 0; i < N; ++i) {
        vector<pair<double,int>> ps;
        const circle &c1 = cs[i];
        ps.push_back(make_pair(-PI, 0));
        ps.push_back(make_pair(PI, 0));
        for(int j = 0; j < N; ++j) {
            if(i == j) continue;
            const circle &c2 = cs[j];
            if(c2.contains(c1)) {
                ps.clear();
                break;
            }
            if(c1.intersects(c2)) {
                const auto tmp = c1.intersection(c2);
                const double arg1 = arg(tmp.first - c1.o);
                const double arg2 = arg(tmp.second - c1.o);
                //cout << i << ' ' << j << ' ' << arg1 << ' ' << arg2 << endl;
                ps.push_back(make_pair(arg1, 1));
                ps.push_back(make_pair(arg2, -1));
                if(arg1 > arg2) {
                    ps.push_back(make_pair(-PI, 1));
                }
            }
        }
        sort(ps.begin(), ps.end());
        int cur = 0;
        double prev = -PI;
        for(const auto &p : ps) {
            if(abs(prev-p.first) > EPS) {
                if(cur == 0) ans += c1.r * abs(p.first - prev);
            }
            cur += p.second;
            prev = p.first;
        }
    }
    printf("%.8f\n", ans);
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;

    return 0;
}
