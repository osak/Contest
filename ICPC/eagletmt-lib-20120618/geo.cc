// vim:fdm=marker:
#include <complex>
#include <cmath>
#include <vector>
using namespace std;
typedef complex<double> P;
static const double PI = acos(-1.0);
static const double EPS = 1e-6;
namespace std {
  bool operator<(const P& a, const P& b)
  {
    if (fabs(a.real() - b.real()) < EPS) {
      return a.imag() < b.imag();
    } else {
      return a.real() < b.real();
    }
  }
};

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
    return a/2.0;
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

// O(N)
vector<P> convex(const vector<P>& ps)/*{{{*/
{
  // assert(sorted(ps.begin(), ps.end()))
  const int N = ps.size();
  vector<P> ch(2*N);
  int k = 0;
  for (int i = 0; i < N; i++) {
    while (k >= 2 && cross(ch[k-1]-ch[k-2], ps[i]-ch[k-2]) <= EPS) {
      k--;
    }
    ch[k] = ps[i];
    k++;
  }
  for (int i = N-2, t = k+1; i >= 0; i--) {
    while (k >= t && cross(ch[k-1]-ch[k-2], ps[i]-ch[k-2]) <= EPS) {
      k--;
    }
    ch[k] = ps[i];
    k++;
  }
  ch.resize(k-1);
  return ch;
}/*}}}*/

struct circle/*{{{*/
{
  P o;
  double r;
  circle() {}
  circle(const P& p, double x) : o(p), r(x) {}

  // POJ 1375 Intervals
  // 点 p を通る2つの接線
  pair<P,P> tangent(const P& p) const
  {
    const double L = abs(o - p);
    const double M = sqrt(L*L - r*r);
    const double theta = asin(r / L);
    const P v = (o - p) / L;
    return make_pair(p + M*(v*polar(1.0, theta)), p + M*(v*polar(1.0, -theta)));
  }

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
    return make_pair(o + e*P(cos_, sin_), o + e*P(cos_, -sin_));
  }

  inline bool contains(const circle& c) const
  {
    return abs(o - c.o)+c.r <= r;
  }

  inline bool intersects(const line& ln) const
  {
    return abs(ln.distance(o)) <= r;
  }

  pair<P,P> intersection(const line& ln) const
  {
    // assert(intersects(ln))
    const P h = ln.perpendicular(o);
    const double d = abs(h - o);
    P ab = ln.b - ln.a;
    ab /= abs(ab);
    const double l = sqrt(r*r - d*d);
    return make_pair(h + l*ab, h - l*ab);
  }
};/*}}}*/

// 3D
struct P3
{
  double x, y, z;
  P3() {}
  P3(double a, double b, double c) : x(a), y(b), z(c) {}
  P3& operator+=(const P3& q) { x += q.x; y += q.y; z += q.z; return *this; }
  P3& operator-=(const P3& q) { x -= q.x; y -= q.y; z -= q.z; return *this; }
  P3& operator*=(double a) { x *= a; y *= a; z *= a; return *this; }
  P3& operator/=(double a) { x /= a; y /= a; z /= a; return *this; }
};
P3 operator+(const P3& p, const P3& q) { P3 r(p); return r += q; }
P3 operator-(const P3& p, const P3& q) { P3 r(p); return r -= q; }
P3 operator*(const P3& p, double a) { P3 q(p); q *= a; return q; }
P3 operator*(double a, const P3& p) { return p*a; }
P3 operator/(const P3& p, double a) { P3 q(p); q /= a; return q; }
P3 operator/(double a, const P3& p) { return p/a; }
inline double dot(const P3& p, const P3& q) { return p.x*q.x + p.y*q.y + p.z*q.z; }
inline double abs(const P3& p) { return sqrt(dot(p, p)); }
inline P3 cross(const P3& a, const P3& b) { return P3(a.y*b.z - b.y*a.z, a.z*b.x - b.z*a.x, a.x*b.y - b.x*a.y); }

struct line3/*{{{*/
{
  P3 a, b;
  line3(const P3& x, const P3& y) : a(x), b(y) {}
};/*}}}*/

struct sphere/*{{{*/
{
  P3 o;
  double r;
  sphere(const P3& p, double x) : o(p), r(x) {}

  // POJ 2149 Inherit the Spheres
  inline bool contains(const sphere& s) const { return abs(o - s.o)+s.r <= r; }
  inline bool intersects(const sphere& s) const { return !contains(s) && !s.contains(*this) && abs(o - s.o) <= r + s.r; }

  // POJ 3944 Spherical Mirros
  bool intersects(const line3& ln) const
  {
    const P3 ab = ln.b - ln.a;
    const P3 ao = o - ln.a;
    if (dot(ab, ao) < 0) {
      return false;
    }
    const double h = abs(cross(ab, ao)) / abs(ab);
    return h < r;
  }

  P3 intersection(const line3& ln) const
  {
    // assert(intersects(ln))
    const P3 ab = ln.b - ln.a;
    const P3 ao = o - ln.a;
    const double h = abs(cross(ab, ao)) / abs(ab);
    const double d = abs(ao);
    const double l = sqrt(d*d - h*h);
    double left = 0.0, right = l/abs(ab);
    for (int i = 0; i < 100; i++) {
      const double mid = (left + right)/2.0;
      const P3 ap = ab*mid;
      const double t = abs(ap - ao);
      if (t < r) {
        right = mid;
      } else {
        left = mid;
      }
    }
    return ln.a + ab*((left + right)/2.0);
  }
};/*}}}*/
