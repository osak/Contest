//Name: Binary Tree on Plane
//Level: 4
//Category: 最小費用流
//Note:

/*
 * 各頂点に対して2つのノードv_i1, v_i2を用意し，頂点iから頂点jへ長さlの辺が張れるときは
 * v_i1からv_j2に重さl，流量1の辺を作成する．
 * 次にSourceから全てのv_i1に重み0，流量2の辺を張り，またv_i2からSinkに重み0，流量1の辺を張る．
 * このグラフにN-1のフローを流せるとき，最小費用流が求める答えとなる．
 */
#include <iostream>
#include <vector>
#include <complex>
#include <cstdio>
#include <queue>

using namespace std;

// 多重辺があっても動く Primal-Dual
// POJ 2047 Concert Hall Scheduling
template <class Flow, class Cost>
struct edge/*{{{*/
{
  int index;
  Flow capacity;
  Cost cost;
  int back;
  edge(int i, Flow c, Cost d, int b) : index(i), capacity(c), cost(d), back(b) {}
};/*}}}*/

template <class Flow, class Cost>
void make_edge(vector<edge<Flow, Cost> > *g, int src, int dst, Flow c, Cost d)/*{{{*/
{
  const int i = g[src].size(), j = g[dst].size();
  g[src].push_back(edge<Flow, Cost>(dst, c, d, j));
  g[dst].push_back(edge<Flow, Cost>(src, 0, -d, i));
}/*}}}*/

const int MAXN = 1000;
const double EPS = 1e-10;
// O(V^2 U C) where
//  U = sum of capacity
//  C = sum of cost
template <class Flow, class Cost>
pair<Flow, Cost>
primal_dual(const vector<edge<Flow, Cost> > *g, int N, int source, int sink, int max_flow)/*{{{*/
{
  pair<Flow, Cost> total;
  Cost h[MAXN], dist[MAXN];
  Flow flow[MAXN][MAXN];
  pair<int,int> parent[MAXN];
  for(int i = 0; i < N; ++i)
      for(int j = 0; j < N; ++j)
          flow[i][j] = 0;

  for (Flow f = max_flow; f > 0; ) {
    fill_n(dist, N, 1000000);
    dist[source] = 0;
    fill_n(parent, N, make_pair(-1, -1));
    priority_queue<pair<Cost,int> > q;
    q.push(make_pair(0, source));
    while (!q.empty()) {
      const int n = q.top().second;
      const Cost c = -q.top().first;
      q.pop();
      if (dist[n]+EPS < c) {
        continue;
      }
      for (typename vector<edge<Flow, Cost> >::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
        const int idx = it - g[n].begin();
        if (it->capacity - flow[n][idx] > 0) {
          const Cost c2 = c + it->cost + h[n] - h[it->index];
          if (c2+EPS < dist[it->index]) {
            dist[it->index] = c2;
            parent[it->index] = make_pair(n, idx);
            q.push(make_pair(-c2, it->index));
          }
        }
      }
    }
    if (parent[sink].first == -1) {
      break;
    }

    Flow e = f;
    for (int i = sink; i != source; i = parent[i].first) {
      const edge<Flow, Cost>& x = g[parent[i].first][parent[i].second];
      e = min(e, x.capacity - flow[parent[i].first][parent[i].second]);
    }
    for (int i = sink; i != source; i = parent[i].first) {
      const edge<Flow, Cost>& x = g[parent[i].first][parent[i].second];
      total.second += e * x.cost;
      //x.flow += e;
      flow[parent[i].first][parent[i].second] += e;
      //g[x.index][x.back].flow -= e;
      flow[x.index][x.back] -= e;
    }
    f -= e;
    total.first += e;
    for (int i = 0; i < N; i++) {
      h[i] += dist[i];
    }
  }

  return total;
}/*}}}*/

typedef complex<double> Point;
typedef edge<int,double> Edge;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    while(cin >> N) {
        vector<Point> points;
        vector<Edge> graph[N*2+2];

        for(int i = 0; i < N; ++i) {
            int x, y;
            cin >> x >> y;
            Point p(x, y);
            for(int j = 0; j < i; ++j) {
                if(points[j].imag() != p.imag()) {
                    double dist = abs(p - points[j]);
                    if(points[j].imag() > p.imag()) {
                        make_edge(graph, j, N+i, 2, dist);
                    } else {
                        make_edge(graph, i, N+j, 2, dist);
                    }
                }
            }
            points.push_back(p);
        }
        // Source to left
        for(int i = 0; i < N; ++i) {
            make_edge(graph, 2*N, i, 2, 0.0);
        }
        // Right to sink
        for(int i = 0; i < N; ++i) {
            make_edge(graph, N+i, 2*N+1, 1, 0.0);
        }
        pair<int,double> res = primal_dual(graph, N*2+2, 2*N, 2*N+1, N-1);
        if(res.first != N-1) {
            puts("-1");
        } else {
            printf("%.7f\n", res.second);
        }
    }
    return 0;
}
