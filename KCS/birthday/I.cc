#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <map>

using namespace std;

typedef complex<double> P;
const double EPS = 1e-7;
const double PI = acos(-1);

inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

// O(N)
vector<P> convex(vector<P>& ps)/*{{{*/
{
  sort(ps.begin(), ps.end(), [](const P &a, const P &b) {
          if(fabs(a.real() - b.real()) < EPS) {
            return a.imag() < b.imag();
          }
          return a.real() < b.real();
          });
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

pair<int,int> bfs(const vector<vector<int>> &graph, int from) {
    vector<bool> visited(graph.size(), false);
    vector<int> q[2];
    visited[from] = true;
    pair<int,int> res(0, from);
    q[0].push_back(from);
    for(int len = 1; q[0].size() > 0; ++len) {
        q[1].clear();
        for(int v : q[0]) {
            for(int to : graph[v]) {
                if(visited[to]) continue;
                visited[to] = true;
                q[1].push_back(to);
            }
        }
        q[0].swap(q[1]);
        if(q[0].size() > 0) {
            res = make_pair(len, q[0][0]);
        }
    }
    return res;
}

int diameter(const vector<vector<int>> &graph) {
    pair<int,int> farest = bfs(graph, 0);
    return bfs(graph, farest.second).first;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    vector<P> points;
    for(int _ = 0; _ < N; ++_) {
        int X, Y, C;
        cin >> X >> Y >> C;
        map<int,int> dict;
        vector<vector<int>> graph;
        for(int i = 0; i < C; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            if(dict.count(a) == 0) {
                const int idx = dict.size();
                dict[a] = idx;
            }
            if(dict.count(b) == 0) {
                const int idx = dict.size();
                dict[b] = idx;
            }
            a = dict[a];
            b = dict[b];
            int s = max(a, b);
            if(graph.size() <= s) {
                graph.resize(s+1);
            }
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        if(graph.size() == C+1) {
            int d = diameter(graph);
            double r = (d+1) / 2;
            //cout << _ << ' ' << r << endl;
            const P c(X, Y);
            const P rot = polar(1.0, 2*PI / 10000);
            P v(r, 0);
            for(int j = 0; j < 20000; ++j) {
                points.push_back(c + v);
                v *= rot;
            }
        }
    }
    vector<P> cvx = convex(points);
    const int S = cvx.size();
    double ans = 0;
    for(int i = 0; i < S; ++i) {
        ans += abs(cvx[i] - cvx[(i+1)%S]);
    }
    printf("%.8f\n", ans);
    return 0;
}
