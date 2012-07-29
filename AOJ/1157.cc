#include <iostream>
#include <complex>
#include <vector>

using namespace std;

typedef complex<double> P;

struct Rect {
    P ps[4];
    int h;

    Rect(const P &lb, const P &ru) {
        ps[0] = lb;
        ps[1] = P(lb.real(), ru.imag());
        ps[2] = ru;
        ps[3] = P(ru.real(), lb.imag());
    }
};

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

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        P start, goal;
        cin >> start.real() >> start.imag() >> goal.real() >> goal.imag();
        const segment road(start, goal);
        vector<Rect> rect;
        double ans = 1e10;
        for(int i = 0; i < N; ++i) {
            int x1, y1, x2, y2;
            int h;
            cin >> x1 >> y1 >> x2 >> y2 >> h;
            const P ps[4];
            ps[0] = P(x1, y1);
            ps[1] = P(x1, y2);
            ps[2] = P(x2, y2);
            ps[3] = P(x2, y1);
            if(road.intersects(segment(ps[0], ps[1])) ||
               road.intersects(segmnet(ps[1], ps[2])) ||
               road.intersects(segment(ps[2], ps[3])) ||
               road.intersects(segment(ps[3], ps[0])))
            {
                ans = 0;
                goto end;
            }

            double mind = 1e10;
            P minp;
            for(int j = 0; j < 4; ++j) {
                double d = road.distance(ps[j]);
                if(d < mind) {
                    mind = d;
                    minp = ps[j];
                }
            }
            corner.push_back(Corner(minp, h));
        }

        double left = 0, right = 1e10;
        for(int TIMES = 0; TIMES < 30; ++TIMES) {
            double mid = (left+right) / 2;
            for(vector<Corner>::iterator it = corner.begin(); it != corner.end(); ++it) {
                // 上から見たとき
                bool col1 = (road.distance(segment(it->ps[0], it->ps[1])) < mid) ||
                            (road.distance(segment(it->ps[1], it->ps[2])) < mid) ||
                            (road.distance(segment(it->ps[2], it->ps[3])) < mid) ||
                            (road.distance(segment(it->ps[3], it->ps[0])) < mid);
                // 横から見たとき
                bool col2 = (:

