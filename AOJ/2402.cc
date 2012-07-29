#include <iostream>
#include <complex>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdio>

using namespace std;

typedef complex<double> P;
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
    while(true) {
        int N, M, L;
        cin >> N >> M >> L;
        if(!N && !M && !L) break;

        vector<segment> segments;
        vector<vector<double> > dist(N*5, vector<double>(N*5, 0));
        for(int i = 0; i < N; ++i) {
            int x, y, a, r;
            cin >> x >> y >> a >> r;
            P base(x, y);
            P pos = polar(double(r), (a+90)*M_PI/180);
            P rot = polar(double(1), 144*M_PI/180);
            for(int i = 0; i < 5; ++i) {
                P next = pos*rot;
                segments.push_back(segment(base+pos, base+next));
                pos = next;
            }
        }
        for(int i = 0; i < segments.size(); ++i) {
            for(int j = 0; j < i; ++j) {
                dist[i][j] = dist[j][i] = segments[i].distance(segments[j]);
            }
        }

        M--; L--;
        priority_queue<pair<double, int> > q;
        q.push(make_pair(0, 5*M));
        vector<double> memo(segments.size(), 1.0/0.0);
        memo[5*M] = 0;

        double ans = -100;
        while(!q.empty()) {
            double cost = -q.top().first;
            int pos = q.top().second;
            q.pop();
            if(cost > memo[pos]) continue;
            if(pos/5 == L) {
                ans = cost;
                break;
            }

            for(int i = 0; i < segments.size(); ++i) {
                double nc = cost + dist[pos][i];
                if(nc < memo[i]) {
                    memo[i] = nc;
                    q.push(make_pair(-nc, i));
                }
            }
        }

        printf("%.7f\n", fabs(ans));
    }

    return 0;
}
