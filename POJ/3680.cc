//Name: Intervals
//Level: 4
//Category: グラフ,Graph,最小費用流
//Note:

/*
 * それぞれのInterval(a,b)の端点に対応する頂点を作り，a->bにコスト-w, 容量1の辺を張る．
 * このようなグラフに対してKのフローを流した時，最小費用流の符号を逆転したものが求める答えとなる．
 * 負辺を持つグラフに対する最小費用流は，Bellman-fordを用いるか，蟻本に書かれている
 * 先に負辺に逆向きのフローを目一杯流したグラフに変形する手法が必要となる．
 * 
 * ここでは後者の手法で解いているが，単純に変形しただけだと辺数が多くなりすぎてPOJだとTLEするため
 * 全ての頂点を左から順に並べ，隣接頂点へ∞の容量を持つ辺を張る，などの工夫が必要．
 *
 * オーダーは O(N^2 K) 程度．
 */
#ifndef ONLINE_JUDGE
//#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
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

typedef edge<int,int> Edge;
typedef vector<Edge> GraphRow;
typedef vector<GraphRow> Graph;

template <class Flow, class Cost>
void make_edge(Graph &g, int src, int dst, Flow c, Cost d)/*{{{*/
{
  const int i = g[src].size(), j = g[dst].size();
  g[src].push_back(edge<Flow, Cost>(dst, c, d, j));
  g[dst].push_back(edge<Flow, Cost>(src, 0, -d, i));
}/*}}}*/

const int MAXN = 410;
// O(V^2 U C) where
//  U = sum of capacity
//  C = sum of cost
template <class Flow, class Cost>
pair<Flow, Cost>
primal_dual(Graph &g, int N, int source, int sink, Flow max_flow)/*{{{*/
{
  pair<Flow, Cost> total;
  static Cost h[MAXN], dist[MAXN];
  static pair<int,int> parent[MAXN];
  for (Flow f = max_flow; f > 0; ) {
    fill_n(dist, N, 100000000);
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

struct Interval {
    int start, end;
    int cost;
};

const int INF = 10000000;
int main() {
    int CASE;
    scanf("%d", &CASE);
    while(CASE--) {
        int N, K;
        scanf("%d %d", &N, &K);
        vector<Interval> intervals(N);
        int ans = 0;
        vector<int> nodes;
        TIMES(i, N) {
            Interval &interval = intervals[i];
            scanf("%d %d %d", &interval.start, &interval.end, &interval.cost);
            nodes.push_back(interval.start);
            nodes.push_back(interval.end);
        }
        sort(nodes.begin(), nodes.end());
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        const int M = nodes.size();
        const int src = M;
        const int sink = M+1;
        const int super_src = M+2;
        const int super_sink = M+3;
        Graph graph(M+4);

        FOREACH(it, intervals) {
            const Interval &interval = *it;
            const int a = distance(nodes.begin(), find(nodes.begin(), nodes.end(), it->start));
            const int b = distance(nodes.begin(), find(nodes.begin(), nodes.end(), it->end));
            //make_edge(graph, a, b, 1, -interval.cost);
            make_edge(graph, b, a, 1, interval.cost);
            ans -= interval.cost;
            make_edge(graph, super_src, b, 1, 0);
            make_edge(graph, a, super_sink, 1, 0);
        }
        TIMES(i, M-1) {
            make_edge(graph, i, i+1, INF, 0);
        }
        make_edge(graph, src, 0, K, 0);
        make_edge(graph, M-1, sink, K, 0);
        make_edge(graph, super_src, src, K, 0);
        make_edge(graph, sink, super_sink, K, 0);

        pair<int,int> res = primal_dual<int,int>(graph, M+4, super_src, super_sink, K+N);
        printf("%d\n", -(ans + res.second));
    }
    return 0;
}
