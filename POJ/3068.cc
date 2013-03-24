//Name: "Shortest" pair of paths
//Level: 3
//Category: グラフ,Graph,最小費用流
//Note:

/*
 * 0からN-1まで流量2のフローを最小コストで流せばよい．
 *
 * オーダーはO(N^2 M C)．
 * ただしCはコストの和．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define TIMES(__i,__n) for(int __i = 0; __i < __n; ++__i)

// 多重辺があっても動く Primal-Dual
// POJ 2047 Concert Hall Scheduling
// Codeforces #170(Div.1)E Binary Tree on Plane
// Costを浮動小数点数にするときは，EPSを考慮しないとDijkstra部で死ぬことがある．
template <class Flow, class Cost>
struct edge/*{{{*/
{
  int index;
  Flow capacity, flow;
  Cost cost;
  int back;
  edge(int i, Flow c, Cost d, int b) : index(i), capacity(c), flow(0), cost(d), back(b) {}
};/*}}}*/

template <class Flow, class Cost>
void make_edge(vector<edge<Flow, Cost> > *g, int src, int dst, Flow c, Cost d)/*{{{*/
{
  const int i = g[src].size(), j = g[dst].size();
  g[src].push_back(edge<Flow, Cost>(dst, c, d, j));
  g[dst].push_back(edge<Flow, Cost>(src, 0, -d, i));
}/*}}}*/

const int MAXN = 64;
// O(V^2 U C) where
//  U = sum of capacity
//  C = sum of cost
template <class Flow, class Cost>
pair<Flow, Cost>
primal_dual(vector<edge<Flow, Cost> > *g, int N, int source, int sink, int max_flow)/*{{{*/
{
  pair<Flow, Cost> total;
  static Cost h[MAXN], dist[MAXN];
  static pair<int,int> parent[MAXN];
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
      if (dist[n] < c) {
        continue;
      }
      for (typename vector<edge<Flow, Cost> >::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
        if (it->capacity - it->flow > 0) {
          const Cost c2 = c + it->cost + h[n] - h[it->index];
          if (c2 < dist[it->index]) {
            dist[it->index] = c2;
            parent[it->index] = make_pair(n, it - g[n].begin());
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
      e = min(e, x.capacity - x.flow);
    }
    for (int i = sink; i != source; i = parent[i].first) {
      edge<Flow, Cost>& x = g[parent[i].first][parent[i].second];
      total.second += e * x.cost;
      x.flow += e;
      g[x.index][x.back].flow -= e;
    }
    f -= e;
    total.first += e;
    for (int i = 0; i < N; i++) {
      h[i] += dist[i];
    }
  }

  return total;
}/*}}}*/

typedef edge<int,int> Edge;
typedef vector<Edge> GraphRow;
typedef vector<GraphRow> Graph;

int main() {
    for(int CASE = 1; ; ++CASE) {
        int N, M;
        scanf("%d %d", &N, &M);
        if(!N && !M) break;

        GraphRow graph[MAXN];
        TIMES(_, M) {
            int a, b, v;
            scanf("%d %d %d", &a, &b, &v);
            make_edge(graph, a, b, 1, v);
        }
        pair<int,int> res = primal_dual(graph, N, 0, N-1, 2);
        printf("Instance #%d: ", CASE);
        if(res.first != 2) {
            puts("Not possible");
        } else {
            printf("%d\n", res.second);
        }
    }
    return 0;
}
