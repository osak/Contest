//Name: Railroad Conflict
//Level: 2
//Category: 幾何,Geometry,線分
//Note:

/**
 * 新幹線の線分と各既存路線の交点をもとめ、始点からの距離でソートする。
 * 交点の地上、地下は一意に決まるので、始点だけ、地下か地上か決めればよい。
 *
 * オーダーはO(N)。
 */
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>

using namespace std;

typedef complex<double> P;

const double PI = acos(-1);
const double EPS = 1e-9;

int cmp(double a, double b) {
    double d = a-b;
    if(abs(d) < EPS) return 0;
    else if(d < 0) return -1;
    return 1;
}

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

  inline P intersection(const segment &s) const {
      return this->intersection(line(s.a, s.b));
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

struct Tag {
    double dist;
    int state;

    Tag() {}
    Tag(double d, int s) : dist(d), state(s) {}

    bool operator <(const Tag &other) const {
        return dist < other.dist;
    }
};

bool solve() {
    double Xa, Ya, Xb, Yb;
    cin >> Xa >> Ya >> Xb >> Yb;
    const P start(Xa, Ya), goal(Xb, Yb);
    const segment seg1(start, goal);

    int N;
    cin >> N;
    vector<Tag> v;
    for(int i = 0; i < N; ++i) {
        double Xs, Ys, Xt, Yt;
        int o, l;
        cin >> Xs >> Ys >> Xt >> Yt >> o >> l;
        const segment seg2(P(Xs, Ys), P(Xt, Yt));
        if(seg1.intersects(seg2)) {
            const P p = seg1.intersection(seg2);
            double dist = abs(p - start);
            v.push_back(Tag(dist, l ^ (1-o)));
        }
    }
    sort(v.begin(), v.end());
    int ans = N+10;
    for(int sl = 0; sl <= 1; ++sl) {
        int cnt = 0;
        int cur = sl;
        for(const auto &t : v) {
            if(t.state != cur) ++cnt;
            cur = t.state;
        }
        ans = min(ans, cnt);
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    while(N--) solve();
    return 0;
}
