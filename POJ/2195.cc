//Name: Going Home
//Level: 3
//Category: グラフ,Graph,最小費用流
//Note:

/*
 * Hとmの間にマンハッタン距離のコストを持つ辺を張り，最小費用流を解く．
 *
 * オーダーは O(V^2 U C)．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <complex>
#include <queue>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define TIMES(__i,__n) for(int __i = 0; __i < __n; ++__i)

// 多重辺があっても動く Primal-Dual
// POJ 2047 Concert Hall Scheduling
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

const int MAXN = 210;
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

typedef complex<int> Point;
typedef edge<int,int> Edge;

vector<Edge> graph[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<Point> hs, ms;
        TIMES(i, N) {
            string str;
            cin >> str;
            TIMES(j, M) {
                if(str[j] == 'H') {
                    hs.push_back(Point(i, j));
                } else if(str[j] == 'm') {
                    ms.push_back(Point(i, j));
                }
            }
        }

        const int K = hs.size();
        TIMES(r, MAXN) {
            graph[r].clear();
        }
        TIMES(mi, K) {
            TIMES(hi, K) {
                const Point diff = ms[mi] - hs[hi];
                make_edge(graph, mi, K+hi, 1, abs(diff.real()) + abs(diff.imag()));
            }
        }
        // Source to m
        TIMES(mi, K) {
            make_edge(graph, K*2, mi, 1, 0);
        }
        // h to Sink
        TIMES(hi, K) {
            make_edge(graph, K+hi, K*2+1, 1, 0);
        }
        pair<int,int> res = primal_dual(graph, K*2+2, K*2, K*2+1, K);
        cout << res.second << endl;
    }
    return 0;
}
