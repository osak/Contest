//Name: Strawberry Cake
//Level: 4
//Category: 幾何
//Note:

/*
 * 角度0とPIで左側の切断の面積は，どちらかが半分より小，どちらかが半分より大となる．
 * したがって中間値の定理より，この間に必ず半分になる角度が存在する．
 * 角度0のときに面積が半分より小さかったとすると，二分探索で範囲を狭めていく時には
 * 常に上記の制約を満たしたまま状態が遷移する．
 * 逆も同様．
 */
#include <iostream>
#include <complex>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define TIMES(i,n) for(int i = 0; i < (n); ++i)

typedef complex<double> P;
static const double PI = acos(-1.0);
static const double EPS = 1e-10;

inline double dot(const P& a, const P& b) { return a.real()*b.real() + a.imag()*b.imag(); }
inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

int ccw(const P& a, P b, P c)
{
  b -= a;
  c -= a;
  if (cross(b, c) > EPS) {
    return +1;
  } else if (cross(b, c) < -EPS) {
    return -1;
  } else if (dot(b, c) < -EPS) {
    return +2;
  } else if (dot(b, b) + EPS < dot(c, c)) {
    return -2;
  } else {
    return 0;
  }
}

struct line/*{{{*/
{
  P a, b;
  line() {}
  line(const P& p, const P& q) : a(p), b(q) {}

  inline bool parallel(const line& ln) const
  {
    return abs(cross(ln.b - ln.a, b - a)) < EPS;
  }

  inline bool intersects(const line& ln) const
  {
    return !parallel(ln);
  }

  inline P intersection(const line& ln) const
  {
    // assert(intersects(ln))
    const P x = b - a;
    const P y = ln.b - ln.a;
    return a + x*(cross(y, ln.a - a))/cross(y, x);
  }

  inline double distance(const P& p) const
  {
    return abs(cross(p - a, b - a)) / abs(b - a);
  }

  // AOJ 1171 Laser Beam Reflections
  inline P perpendicular(const P& p) const
  {
    // 点 p から直線上に下ろした垂線の足
    const double t = dot(p-a, a-b) / dot(b-a, b-a);
    return a + t*(a-b);
  }
};/*}}}*/

struct segment/*{{{*/
{
  P a, b;
  segment() {}
  segment(const P& x, const P& y) : a(x), b(y) {}

  inline bool intersects(const line& ln) const
  {
    return cross(ln.b - ln.a, a - ln.a) * cross(ln.b - ln.a, b - ln.a) < EPS;
  }

  // AOJ 2402 Milkey Way
  inline bool intersects(const segment& seg) const
  {
    return ccw(a, b, seg.a) * ccw(a, b, seg.b) <= 0
      && ccw(seg.a, seg.b, a) * ccw(seg.a, seg.b, b) <= 0;
  }

  // AOJ 1171 Laser Beam Relections
  inline P intersection(const line& ln) const
  {
    // assert(intersects(ln))
    const P x = b - a;
    const P y = ln.b - ln.a;
    return a + x*(cross(y, ln.a - a))/cross(y, x);
  }

  inline bool parallel(const line& ln) const
  {
    return abs(cross(ln.b - ln.a, b - a)) < EPS;
  }

  // AOJ 2402 Milkey Way
  inline double distance(const P& p) const
  {
    if (dot(b-a, p-a) < EPS) {
      return abs(p-a);
    } else if (dot(a-b, p-b) < EPS) {
      return abs(p-b);
    } else {
      return abs(cross(b-a, p-a))/abs(b-a);
    }
  }

  // AOJ 2402 Milkey Way
  inline double distance(const segment& seg) const
  {
    if (intersects(seg)) {
      return 0;
    } else {
      return
        min(
            min(distance(seg.a), distance(seg.b)),
            min(seg.distance(a), seg.distance(b)));
    }
  }
};/*}}}*/

struct polygon/*{{{*/
{
  vector<P> ps;
  polygon() {}
  polygon(const vector<P>& v) : ps(v) {}

  inline int size() const { return ps.size(); }
  inline void push_back(const P& p) { ps.push_back(p); }
  inline P& operator[](int i) { return ps[i]; }
  inline const P& operator[](int i) const { return ps[i]; }

  double area() const
  {
    // positive if polygon is clockwise
    double a = 0.0;
    const int N = ps.size();
    for (int i = 0; i < N; i++) {
      a += cross(ps[(i+1)%N], ps[i]);
    }
    return abs(a)/2.0;
  }

  polygon cut(const line& ln) const
  {
    // cut out the left-side of the line
    const int N = ps.size();
    polygon ret;
    for (int i = 0; i < N; i++) {
      const segment seg(ps[i], ps[(i+1)%N]);
      if (cross(ln.b - ln.a, ps[i] - ln.a) < EPS) {
        // ps[i] is right-side of the line
        ret.push_back(ps[i]);
        if (!seg.parallel(ln) && seg.intersects(ln)) {
          const P p = seg.intersection(ln);
          if (abs(p - ps[i]) > EPS) {
            ret.push_back(p);
          }
        }
      } else if (!seg.parallel(ln) && seg.intersects(ln)) {
        ret.push_back(seg.intersection(ln));
      }
    }
    return ret;
  }
};/*}}}*/

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    while(cin >> N) {
        if(!N) break;
        vector<P> points;
        TIMES(_, N) {
            P point;
            cin >> point.real() >> point.imag();
            points.push_back(point);
        }
        polygon poly(points);
        const double target = poly.area() / 2;
        double l = 0, r = PI;
        const double area_l = poly.cut(line(P(0,0), polar(10.0, l))).area();
        const double area_r = poly.cut(line(P(0,0), polar(10.0, r))).area();
        TIMES(_, 100) {
            const double center = (l+r) / 2;
            const double area = poly.cut(line(P(0,0), polar(10.0, center))).area();
            if(area_l < area_r) {
                if(area < target) l = center;
                else r = center;
            } else {
                if(area < target) r = center;
                else l = center;
            }
        }
        const P ans = polar(10.0, (l+r)/2);
        printf("%.15f %.15f\n", ans.real(), ans.imag());
    }
    return 0;
}
