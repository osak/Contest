//Name: Laser Beam Reflection
//Level: 4
//Category: 幾何
//Note:

/*
 * 鏡に反射してゴールする = 鏡に対して線対称な位置にゴールを移動し，その鏡を突き抜けた直線で結べる
 * という事実を使う．
 * ゴール直前の反射から最初の反射までを逆順にたどると，スタートからどの位置を狙えばゴールに行く反射になるかが分かる．
 * この角度が分かったら，反射の系列が正当なものである(他の鏡に邪魔されない，ちゃんと目的の鏡に反射する)ことを確認していく．
 */
#include <iostream>
#include <complex>
#include <vector>
#include <cstdio>

using namespace std;

typedef complex<double> P;
static const double PI = acos(-1.0);
static const double EPS = 1e-6;

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


ostream& operator <<(ostream &o, const pair<double,double> &p) {
    return o << '(' << p.first << ',' << p.second << ')';
}

bool check(const vector<int> &seq, const P &start_, const P &goal_, const vector<segment> &mirrors) {
    P start = start_;
    P goal = goal_;

    int prev = -1;
    for(int i = (int)seq.size()-1; i >= 0; --i) {
        segment vec(start, goal);

        // mirrors[i] に最初にぶつかることを確認する．
        double cross_dist = 1e100;
        int cross_idx = -1;
        P cross_point;
        for(int j = 0; j < (int)mirrors.size(); ++j) {
            if(j == prev) continue;
            if(mirrors[j].intersects(vec)) {
                P cp = mirrors[j].intersection(line(vec.a, vec.b));
                double dist = abs(cp - start);
                if(dist < cross_dist) {
                    cross_idx = j;
                    cross_dist = dist;
                    cross_point = cp;
                }
            }
        }
        if(cross_idx != seq[i]) return false;

        P perp = line(mirrors[seq[i]].a, mirrors[seq[i]].b).perpendicular(goal);
        goal = goal + (perp-goal)*2.0;
        start = cross_point;
        prev = seq[i];
    }

    // 最後に鏡にぶつからずにゴールできることを確認する．
    {
        segment vec(start, goal);
        for(int i = 0; i < (int)mirrors.size(); ++i) {
            if(i == prev) continue;
            if(mirrors[i].intersects(vec)) return false;
        }
    }
    return true;
}

double dfs(vector<int> &seq, const P &start, const P &goal, const vector<segment> &mirrors) {
    double ans = 1e100;
    if(check(seq, start, goal, mirrors)) {
        ans = min(ans, abs(goal-start));
    }

    if(seq.size() == 5) return ans;
    for(int i = 0; i < (int)mirrors.size(); ++i) {
        if(seq.size() > 0 && i == seq.back()) continue;
        seq.push_back(i);
        P perp = line(mirrors[i].a, mirrors[i].b).perpendicular(goal);
        P next_goal = goal + (perp-goal)*2.0;
        ans = min(ans, dfs(seq, start, next_goal, mirrors));
        seq.pop_back();
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<segment> mirrors;
        for(int i = 0; i < N; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            mirrors.push_back(segment(P(x1, y1), P(x2, y2)));
        }

        P start, goal;
        cin >> goal.real() >> goal.imag();
        cin >> start.real() >> start.imag();

        vector<int> seq;
        double ans = dfs(seq, start, goal, mirrors);
        printf("%.5f\n", ans);
    }
    return 0;
}
