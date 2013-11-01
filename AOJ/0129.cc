//Name: Hide-and-Seek Supporting System
//Level: 2
//Category: 幾何,Geometry,円
//Note:

/**
 * 位置の組が与えられたら、その直線上と各円との交点を列挙する。
 * これらの交点のうち、与えられた線分の上に乗っているものがあれば鬼からは見えない。
 * オーダーはO(N+M)。
 */
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>

using namespace std;

typedef complex<double> P;
const double EPS = 1e-9;
const double PI = acos(-1);

bool in_range(double a, double x, double b) {
    return a-EPS <= x && x <= b+EPS;
}

inline double dot(const P& a, const P& b) { return a.real()*b.real() + a.imag()*b.imag(); }
inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

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

bool solve() {
    int N;
    cin >> N;
    if(!N) return false;

    vector<circle> walls(N);
    for(int i = 0; i < N; ++i) {
        double x, y, r;
        cin >> x >> y >> r;
        walls[i] = circle(P(x, y), r);
    }

    int M;
    cin >> M;
    while(M--) {
        double tx, ty, sx, sy;
        cin >> tx >> ty >> sx >> sy;
        const P T(tx, ty), S(sx, sy);
        const line L(T, S);
        const double len(abs(T - S));
        const bool res = any_of(walls.begin(), walls.end(), [&](const circle &c) {
                if(!c.intersects(L)) return false;
                const auto ps = c.intersection(L);
                const double d1 = dot(ps.first - T, S - T);
                if(in_range(0, d1/len/len, 1)) return true;
                const double d2 = dot(ps.second - T, S - T);
                if(in_range(0, d2/len/len, 1)) return true;
                return false;
                });
        cout << (res ? "Safe" : "Danger") << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
