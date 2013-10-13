//Name: UFO Shooting Down Operation
//Level: 3
//Category: 幾何,Geometry,円
//Note: 問題文が曖昧。R内に中心が入ったUFOは無敵化するとしてよい。

/**
 * 各UFOの動きをシミュレーションしつつ、問題文のとおりに
 * 一番近いUFOを選び、その向きに半直線を取る。
 * この半直線とUFOの円との交点が、原点から距離Rを超えたところにあるとき、そのUFOは撃墜される。
 *
 * 問題文では「かすった」の定義が曖昧で、中心はR以下の点にあるが円全体は外側にはみ出しているような
 * UFOに対し、他のUFOを狙った結果としてレーザーが外側で交差するときの処理が一意に決められない。
 * 正解は、R内に中心が入ったUFOは即座に無敵化するものと扱う。
 *
 * オーダーはO(N^2)。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>

using namespace std;

typedef complex<double> P;
const double PI = acos(-1);
const double EPS = 1e-9;

int cmp(double a, double b) {
    const double d = a-b;
    if(abs(d) < EPS) return 0;
    else if(d < 0) return -1;
    return 1;
}

inline double dot(const P& a, const P& b) { return a.real()*b.real() + a.imag()*b.imag(); }

struct line/*{{{*/
{
  P a, b;
  line() {}
  line(const P& p, const P& q) : a(p), b(q) {}

  // AOJ 1171 Laser Beam Reflections
  inline P perpendicular(const P& p) const
  {
    // 点 p から直線上に下ろした垂線の足
    const double t = dot(p-a, a-b) / dot(b-a, b-a);
    return a + t*(a-b);
  }

  inline double distance(const P& p) const {
      return abs(p - this->perpendicular(p));
  }
};/*}}}*/

struct circle/*{{{*/
{
  P o;
  double r;
  circle() {}
  circle(const P& p, double x) : o(p), r(x) {}

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

struct UFO {
    P pos, dv;
    double r;

    UFO() {}
    UFO(const P &p, double r, double v) : pos(p), r(r) {
        dv = pos * v / abs(pos);
    }

    void move() {
        if(cmp(abs(dv), abs(pos)) >= 0) {
            pos = P(0, 0);
        } else {
            pos -= dv;
        }
    }
};

bool check(const P &p, const P &dir, double R) {
    if(dot(p, dir) < 0) return false;
    return cmp(abs(p), R) > 0;
}

bool solve() {
    int R, N;
    cin >> R >> N;
    if(!R && !N) return false;

    vector<UFO> ufos;
    for(int i = 0; i < N; ++i) {
        double x, y, r, v;
        cin >> x >> y >> r >> v;
        ufos.push_back(UFO(P(x, y), r, v));
    }
    int ans = 0;
    while(true) {
        const int M = ufos.size();
        double min_dist = 1e10;
        int min_idx = -1;
        for(int i = 0; i < M; ++i) {
            UFO &u = ufos[i];
            u.move();
            const double d = abs(u.pos);
            if(cmp(d, R) > 0 && d < min_dist) {
                min_dist = d;
                min_idx = i;
            }
        }
        if(min_idx == -1) break;
        //cout << ufos[min_idx].pos << endl;
        const line l(P(0, 0), ufos[min_idx].pos);
        auto pend = remove_if(ufos.begin(), ufos.end(), [&](const UFO &u) {
                const circle c(u.pos, u.r);
                if(cmp(abs(u.pos), R) <= 0) return false;
                if(!c.intersects(l)) return false;
                const auto tmp = c.intersection(l);
                return check(tmp.first, l.b, R) || check(tmp.second, l.b, R);
                });
        //cout << distance(pend, ufos.end()) << endl;
        ufos.erase(pend, ufos.end());
    }
    cout << ufos.size() << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
