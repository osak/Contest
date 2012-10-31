//Name: Elune’s Arrow
//Level: 3
//Category: 幾何
//Note:

/*
 * まず目標を構成する線分のどれかに当たるかを計算し，当たるなら一番近い交点の距離を記憶しておく．
 * そのあと他の物体で同じことを行ない，目標物体より距離の近い交点を持つものがなければHIT．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <complex>

using namespace std;

typedef complex<double> P;
static const double EPS = 1e-9;

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
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(true) {
        int N;
        cin >> N;
        if(!N) break;
        P origin, vec;
        cin >> origin.real() >> origin.imag() >> vec.real() >> vec.imag();
        vec += origin;
        const line arrow(origin, vec);
        vector<vector<P> > enemies(N);
        for(int i = 0; i < N; ++i) {
            int M;
            cin >> M;
            while(M--) {
                int x, y;
                cin >> x >> y;
                enemies[i].push_back(P(x, y));
            }
        }
        //cout << arrow.a << ' ' << arrow.b << endl;
        // Check if hits target
        bool hit = false;
        double hit_a = 1e50;
        for(int i = 0; i < (int)enemies[0].size(); ++i) {
            segment seg(enemies[0][i], enemies[0][(i+1)%enemies[0].size()]);
            if(seg.intersects(arrow)) {
                //cout << i << endl;
                P pos = seg.intersection(arrow);
                //cout << pos << endl;
                if(dot(pos-origin, vec-origin) > 0) {
                    hit_a = min(hit_a, abs(pos-origin));
                    hit = true;
                    //cout << hit_a << endl;
                }
            }
        }
        if(hit) {
            // Check if hit point is nearest
            for(int j = 1; j < N; ++j) {
                for(int i = 0; i < (int)enemies[j].size(); ++i) {
                    segment seg(enemies[j][i], enemies[j][(i+1)%enemies[j].size()]);
                    if(seg.intersects(arrow)) {
                        P pos = seg.intersection(arrow);
                        if(dot(pos-origin, vec-origin) > 0 && abs(pos-origin) < hit_a) {
                            hit = false;
                            goto end;
                        }
                    }
                }
            }
        }
end:
        cout << (hit?"HIT":"MISS") << endl;
    }
    return 0;
}
