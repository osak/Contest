//Name: Kuru-Kuru Robot
//Level: 3
//Category: 幾何,Geometry,グラフ,Graph,線分アレンジメント,角度,練習問題
//Note:

/**
 * 線分アレンジメントを行ってグラフを作る。
 * 回転のコストを求めるためには、最後にたどった線分の角度を覚えておき、次にたどりたい線分の角度との差分を計算すればよい。
 * これは、グラフを拡張して、(頂点,直前にいた頂点)を新しい頂点としたグラフにすれば実現できる。
 * このグラフの上で、最短経路問題を解けば良い。
 *
 * 線分アレンジメントでは、最大で N(N-1) = O(N^2) 個の頂点が生成され得る。
 * したがって、拡張後のグラフの頂点数は O(N^3)（各頂点について、最大2N本の辺が接続し得るため）。
 * オーダーはO(N^4 log N)。
 * （線分アレンジメントに O(N^2)、拡張後は各頂点が最大2N辺をもつため、辺数は O(N^4) となる）
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
#include <unordered_map>
#include <queue>

using namespace std;

typedef complex<double> P;
const double EPS = 1e-9;
const double PI = acos(-1);

namespace std {
  bool operator<(const P& a, const P& b)
  {
    if (fabs(a.real() - b.real()) < EPS) {
      return a.imag() < b.imag();
    } else {
      return a.real() < b.real();
    }
  }

  bool operator ==(const P& a, const P& b) {
      return abs(a-b) < EPS;
  }
};
struct Hash {
    size_t operator()(const pair<int,int> &p) const {
        return p.first * 2500 + p.second;
    }
};

inline double dot(const P& a, const P& b) { return a.real()*b.real() + a.imag()*b.imag(); }
inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

int ccw(const P& a, P b, P c)
{
  b -= a;
  c -= a;
  if (cross(b, c) > EPS) { // ccw
    return +1;
  } else if (cross(b, c) < -EPS) { // cw
    return -1;
  } else if (dot(b, c) < -EPS) { // c-a-b or b-a-c
    return +2;
  } else if (dot(b, b) + EPS < dot(c, c)) { // a-b-c
    return -2;
  } else { // a-c-b
    return 0;
  }
}

struct segment/*{{{*/
{
  P a, b;

  segment() {}
  segment(const P& x, const P& y) : a(x), b(y) {}
  // AOJ 2402 Milkey Way
  inline bool intersects(const segment& seg) const
  {
    return ccw(a, b, seg.a) * ccw(a, b, seg.b) <= 0
      && ccw(seg.a, seg.b, a) * ccw(seg.a, seg.b, b) <= 0;
  }

  // AOJ 1171 Laser Beam Relections
  inline P intersection(const segment& ln) const
  {
    // assert(intersects(ln))
    const P x = b - a;
    const P y = ln.b - ln.a;
    return a + x*(cross(y, ln.a - a))/cross(y, x);
  }
};/*}}}*/

double calc_cost(const P &a, const P &b) {
    double angle = arg(a) - arg(b);
    while(angle < 0) angle += 2*PI;
    while(angle > 2*PI) angle -= 2*PI;
    return min(angle, 2*PI-angle);
}

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<segment> segments;
    for(int i = 0; i < N; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        segments.emplace_back(P(x1, y1), P(x2, y2));
    }

    vector<P> nodes;
    for(int i = 0; i < N; ++i) {
        const segment &s1 = segments[i];
        for(int j = 0; j < i; ++j) {
            const segment &s2 = segments[j];
            if(s1.intersects(s2)) {
                nodes.push_back(s1.intersection(s2));
            }
        }
        nodes.push_back(s1.a);
        nodes.push_back(s1.b);
    }
    sort(begin(nodes), end(nodes));
    nodes.erase(unique(begin(nodes), end(nodes)), end(nodes));

    const int M = nodes.size();
    vector<vector<int>> graph(nodes.size());
    for(const segment &seg : segments) {
        vector<pair<double,int>> ps;
        for(int i = 0; i < M; ++i) {
            if(ccw(seg.a, nodes[i], seg.b) == -2 || seg.a == nodes[i] || seg.b == nodes[i]) {
                ps.emplace_back(abs(nodes[i] - seg.a), i);
            }
        }
        sort(begin(ps), end(ps));
        for(int i = 0; i+1 < ps.size(); ++i) {
            graph[ps[i].second].push_back(ps[i+1].second);
            graph[ps[i+1].second].push_back(ps[i].second);
        }
    }

    int sx, sy, gx, gy;
    cin >> sx >> sy >> gx >> gy;
    const P sp(sx, sy), gp(gx, gy);

    int start = -1, goal = -1;
    for(int i = 0; i < M; ++i) {
        if(nodes[i] == sp) {
            start = i;
        }
        if(nodes[i] == gp) {
            goal = i;
        }
    }
    if(start == -1 || goal == -1) {
        cout << "-1" << endl;
        return true;
    }

    unordered_map<pair<int,int>, double, Hash> memo;
    priority_queue<pair<double, pair<int,int>>> q;
    q.push(make_pair(0, make_pair(-1, start)));
    double ans = -1;
    while(!q.empty()) {
        const double cost = -q.top().first;
        const int prev = q.top().second.first;
        const int cur = q.top().second.second;
        q.pop();
        const auto key = make_pair(prev, cur);
        if(memo[key] < cost) continue;
        if(cur == goal) {
            ans = cost;
            break;
        }

        for(int next : graph[cur]) {
            double nc = 0;
            if(prev == -1) {
                nc = 0;
            } else {
                const P v1 = nodes[cur] - nodes[prev];
                const P v2 = nodes[next] - nodes[cur];
                nc = cost + calc_cost(v1, v2);
            }
            const auto nkey = make_pair(cur, next);
            if(!memo.count(nkey) || memo[nkey] > nc) {
                memo[nkey] = nc;
                q.push(make_pair(-nc, nkey));
            }
        }
    }
    if(ans < 0) cout << -1 << endl;
    else cout << ans*180/PI << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) ;
    return 0;
}
