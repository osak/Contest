//Name: A Round Peg in a Ground Hole
//Level: 3
//Category: 幾何,凸性判定,点と線分の距離
//Note:

/*
 * まず多角形が凸かどうかを調べ，次にその中に半径 R の円が入るかを調べればよい．
 * 凸かどうかは頂点を順にたどっていったとき， ccw の符号が常に一致しているかで決まる．
 * 円が多角形の中に入るかどうかは，まず中心が多角形の中に入っているかを確認し，入っていたら
 * どの線分とも距離 R 以上離れているかどうかを確認する．
 * 中心が凸多角形の中に入っているかどうかは，中心から多角形の各頂点に線分を引き，分割された
 * 三角形の面積を足したものが凸多角形の面積そのものと等しいかどうかで判定できる．
 * (もしもこの点が凸多角形の外にある場合，必ず合計値は真の面積より大きくなる．)
 *
 * オーダーは O(N)．
 */
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

typedef complex<double> P;
static const double EPS = 1e-8;

inline bool eqv(double a, double b) {
    return fabs(a-b) < EPS;
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
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int N;
        double R, X, Y;
        cin >> N >> R >> X >> Y;
        if(N < 3) break;

        vector<P> points(N);
        for(int i = 0; i < N; ++i) {
            cin >> points[i].real() >> points[i].imag();
        }

        // Check if hole is well-formed
        bool well_formed = true;
        int dir = 0;
        for(int i = 0; i < N; ++i) {
            const int next1 = (i+1) % N;
            const int next2 = (i+2) % N;
            const int c = ccw(points[i], points[next1], points[next2]);
            if(c == -2) continue;
            else if(c == +2 || c == 0) {
                well_formed = false;
                break;
            } else {
                if(dir * c < 0) {
                    well_formed = false;
                    break;
                }
                dir = c;
            }
        }
        if(!well_formed) {
            cout << "HOLE IS ILL-FORMED" << endl;
            continue;
        }

        const P center(X, Y);
        bool fit = true;
        // Check if peg is in polygon
        double area1 = 0, area2 = 0;
        for(int i = 0; i < N; ++i) {
            const P v1 = points[(i+1)%N] - center;
            const P v2 = points[i] - center;
            double tmp = cross(v1, v2);
            area1 += tmp;
            area2 += fabs(tmp);
        }
        if(eqv(fabs(area1), fabs(area2))) {
            // Check if all segments is at least R far from center
            for(int i = 0; i < N; ++i) {
                segment seg(points[i], points[(i+1)%N]);
                if(seg.distance(center) < R) {
                    fit = false;
                    break;
                }
            }
        } else {
            fit = false;
        }
        if(fit) {
            cout << "PEG WILL FIT" << endl;
        } else {
            cout << "PEG WILL NOT FIT" << endl;
        }
    }
    return 0;
}
