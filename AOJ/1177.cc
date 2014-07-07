//Name: Watchdog Corporation
//Level: 5
//Category: 幾何,Geometry,場合分け
//Note:

/**
 * 簡単のため、建物は必ずy > 0の領域に存在し、第一象限に可能な限り多くの部分を置くものとする。
 * このとき、犬の動ける領域を考えると、y < 0では常に半円形になる。
 * y > 0 では、反時計回りに0 radから3/2πrad、時計回りにπradから-1/2πradの範囲を考えればよい
 * （これ以上を考えても、逆回りのほうが効率がよいのは明らか）。
 * また、フェンスの配置を考える時、反時計回りと時計回りは高々1回しか交差しない
 * （交差した時点で、それより後の領域では競り負けることが明らか）。
 * したがって、先に反時計回りの円弧を列挙しておき、あとから時計回りの円弧をひとつずつ追加しながら、
 * 最初に交差した円弧から先を無視するようにすればよい。
 *
 * 円弧の計算は、反時計回りのものを1つ考えれば、x座標を反転させることで時計回りの回転にも対応できる。
 * 原点から建物に引っかかるまでの扱いに気をつければ、その後は壁にぶつかるパターンに注意しつつ、簡単に求められる。
 *
 * オーダーは O(N)。
 * ただし、Nは辺の数（=4）。
 * 矩形以外でも同じようにできるんだろうか？
 */
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <cassert>

using namespace std;

typedef complex<double> P;

const double PI = acos(-1);
const double EPS = 1e-13;

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
    return make_pair(o + e*P(cos_, sin_), o + e*P(cos_, -sin_));
  }

  inline bool contains(const circle& c) const
  {
    return abs(o - c.o)+c.r <= r;
  }
};/*}}}*/

inline bool in_range(const double a, const double x, const double b) {
    return a < x && x < b;
}

struct arc {
    circle c;
    double start, end;

    arc() {}
    arc(const circle &c, double s, double e) : c(c), start(s), end(e) {}

    P intersection(const arc &other) const {
        auto ps = c.intersection(other.c);
        auto p1 = ps.first;
        if(in_range(start, arg(p1 - c.o), end) && in_range(other.start, arg(p1 - other.c.o), other.end)) return p1;
        return ps.second;
    }

    bool intersects(const arc &other) const {
        if(c.intersects(other.c)) {
            auto p = intersection(other);
            return in_range(start, arg(p - c.o), end) && in_range(other.start, arg(p - other.c.o), other.end);
        }
        return false;
    }

    double length() const {
        return c.r * (end - start);
    }
};

vector<arc> calc(double len, double x1, double y1, double x2, double y2) {
    vector<arc> res;
    if(x2 <= 0 + EPS) {
        if(abs(P(x2, y1)) + EPS >= len) {
            // Do not touch
            res.push_back(arc(circle(P(0, 0), len), 0, PI));
            return res;
        } else if(abs(P(x2, y2)) + EPS >= len) {
            // Crash into right wall
            res.push_back(arc(circle(P(0, 0), len), 0, PI - acos(-x2 / len)));
            return res;
        } else {
            res.push_back(arc(circle(P(0, 0), len), 0, arg(P(x2, y2))));
            len -= abs(P(x2, y2));
            res.push_back(arc(circle(P(x2, y2), len), res.back().end, PI));
            len -= x2 - x1;
            if(len <= 0 + EPS) return res; // crash into top wall
            res.push_back(arc(circle(P(x1, y2), len), res.back().end, PI + PI / 2));
            return res;
        }
    } else {
        if(abs(P(x2, y1)) + EPS >= len) {
            // crash into bottom wall
            res.push_back(arc(circle(P(0, 0), len), 0, asin(y1 / len)));
            return res;
        } else {
            res.push_back(arc(circle(P(0, 0), len), 0, arg(P(x2, y1))));
            len -= abs(P(x2, y1));
            res.push_back(arc(circle(P(x2, y1), len), res.back().end, PI / 2));
            len -= y2 - y1;
            if(len <= 0 + EPS) return res; // crash into right wall
            res.push_back(arc(circle(P(x2, y2), len), res.back().end, PI));
            len -= x2 - x1;
            if(len <= 0 + EPS) return res; // crash into top wall
            res.push_back(arc(circle(P(x1, y2), len), res.back().end, PI + PI / 2));
            return res;
        }
    }
}

bool solve() {
    int len;
    int x1, y1, x2, y2;
    if(!(cin >> len >> x1 >> y1 >> x2 >> y2)) return false;
    if(len == 0 && x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0) return false;

    // make sure building is at y > 0
    if(y1 <= 0 && y2 >= 0) {
        // swap axis
        swap(x1, y1);
        swap(x2, y2);
    }
    if(y2 < 0) {
        // flip y axis
        double tmp = y1;
        y1 = -y2;
        y2 = -tmp;
    }
    if(x2 < 0 || abs(x1) > abs(x2)) {
        // flip x axis
        double tmp = x1;
        x1 = -x2;
        x2 = -tmp;
    }

    double ans = 0.0 / 0.0;
    //cout << len << ' ' << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << abs(P(x1, y1)) << ' ' << abs(P(x2, y1)) << endl;
    if(y1 >= len || (x1 >= 0 && abs(P(x1, y1)) + EPS >= len)) {
        ans = 2 * PI * len;
    } else {
        auto right = move(calc(len, x1, y1, x2, y2));
        auto left = move(calc(len, -x2, y1, -x1, y2));
        for(auto &arc : left) {
            arc.c.o.real(-arc.c.o.real());
            swap(arc.start, arc.end);
            arc.start = PI - arc.start;
            arc.end = PI - arc.end;
            assert(arc.start < arc.end);
        }
        // Check if arc from left intersects into arc from right
        ans = len * PI;
        for(auto &arc_l : left) {
            bool intersected = false;
            for(auto &arc_r : right) {
                if(intersected) {
                    arc_r.start = arc_r.end = 0;
                } else if(arc_l.intersects(arc_r)) {
                    const P p = arc_l.intersection(arc_r);
                    arc_l.start = arg(p - arc_l.c.o);
                    arc_r.end = arg(p - arc_r.c.o);
                    intersected = true;
                }
            }
            ans += arc_l.length();
            if(intersected) break;
        }
        for(auto &arc : right) ans += arc.length();
        //for(auto &arc : left) ans += arc.length();
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
