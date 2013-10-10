//Name: Immortal Jewels
//Level: 3
//Category: 幾何,Geometory,円
//Note:

/**
 * それぞれの宝石について、半径をm_iだけ拡大した円を追加して考えると、
 * 直線を動かしていって取れる個数が変化する瞬間には、その直線はこれらの円のうちどれか2円の接線になっている。
 * したがって、すべての2円の組み合わせに対する接線を列挙し、取れる個数を確認すればよい。
 *
 * オーダーはO(N^3)。
 */
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include <cassert>

using namespace std;

typedef complex<double> P;
const double PI = acos(-1);
const double EPS = 1e-12;

int cmp(double a, double b) {
    const double diff = a - b;
    if(fabs(diff) < EPS) return 0;
    else if(diff < 0) return -1;
    else return 1;
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

  pair<line,line> outer_tangent_parallel(const circle &c) const {
      const P d = o - c.o;
      const P v = d * P(0, 1) * r / abs(d);
      return make_pair(line(o+v, c.o+v), line(o-v, c.o-v));
  }

  pair<line,line> outer_tangent(const circle &c) const {
      if(cmp(r, c.r) == 0) return outer_tangent_parallel(c);
      if(r > c.r) return c.outer_tangent(*this);
      const P d = o - c.o;
      const double fact = c.r/r - 1;
      const P base = c.o + d+d/fact;
      const pair<P,P> t = tangent(base);
      return make_pair(line(base, t.first), line(base, t.second));
  }

  pair<line,line> inner_tangent(const circle &c) const {
      if(r > c.r) return c.inner_tangent(*this);
      const P d = c.o - o;
      const double fact = c.r/r + 1;
      const P base = o + d/fact;
      const pair<P,P> t = tangent(base);
      return make_pair(line(base, t.first), line(base, t.second));
  }

  // POJ 1418 Viva Confetti
  // POJ 2149 Inherit the Spheres
  inline bool intersects(const circle& c) const
  {
    return !contains(c) && !c.contains(*this) && cmp(abs(o - c.o), r + c.r) <= 0;
  }

  inline bool independent(const circle &c) const {
      return cmp(abs(o-c.o), r+c.r) > 0;
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
    return cmp(abs(o - c.o)+c.r, r) < 0;
  }

  inline bool intersects(const line& ln) const
  {
    return cmp(abs(ln.distance(o)), r) <= 0;
  }

  inline double distance(const line &ln) const {
      return abs(ln.distance(o));
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

void enum_event(const circle &c1, const circle &c2, vector<line> &lines) {
    if(c1.independent(c2)) {
        auto outer = c1.outer_tangent(c2);
        lines.push_back(outer.first);
        lines.push_back(outer.second);
        auto inner = c1.inner_tangent(c2);
        lines.push_back(inner.first);
        lines.push_back(inner.second);
    } else if(c1.intersects(c2)) {
        auto outer = c1.outer_tangent(c2);
        lines.push_back(outer.first);
        lines.push_back(outer.second);
        auto inter = c1.intersection(c2);
        lines.push_back(line(inter.first, inter.second));
    } 
}

bool solve() {
    int N;
    cin >> N;
    if(!N) return false;

    vector<pair<circle,circle>> jewels;
    vector<line> lines;
    for(int i = 0; i < N; ++i) {
        double x, y, r, m;
        cin >> x >> y >> r >> m;
        const P center(x, y);
        pair<circle,circle> jewel = make_pair(circle(center, r), circle(center, r+m));
        for(const auto &other : jewels) {
            enum_event(jewel.first, other.first, lines);
            enum_event(jewel.first, other.second, lines);
            enum_event(jewel.second, other.first, lines);
            enum_event(jewel.second, other.second, lines);
        }
        jewels.push_back(jewel);
    }

    int ans = 1;
    for(auto &l : lines) {
        int cnt = count_if(jewels.begin(), jewels.end(), [&](const pair<circle,circle> &j){
                return cmp(j.first.r, j.first.distance(l)) <= 0 && 
                cmp(j.second.r, j.second.distance(l)) >= 0;
                });
        ans = max(ans, cnt);
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;

    return 0;
}
