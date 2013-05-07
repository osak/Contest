//Name: Kaka's Matrix Travels
//Level: 3
//Category: グラフ,Graph,最小費用流
//Note:

/*
 * 各ノードに出島をつけて，対応するノードとの間に(-v,1)の辺と(INF,0)の辺を張る．
 * 出島からは下と右のノードに辺を張る．
 * このグラフで最小費用流を求めればよい．
 * (ただし，ナイーブなBellman-fordだとPOJでTLEするので最適化が必要)
 *
 * オーダーは O(N^3 K)．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

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

typedef edge<int,int> Edge;

template <class Flow, class Cost>
void make_edge(vector<edge<Flow, Cost> > *g, int src, int dst, Flow c, Cost d)/*{{{*/
{
  const int i = g[src].size(), j = g[dst].size();
  g[src].push_back(edge<Flow, Cost>(dst, c, d, j));
  g[dst].push_back(edge<Flow, Cost>(src, 0, -d, i));
}/*}}}*/

const int MAXN = 50*50*2+10;

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
    queue<int> q;
    q.push(source);
    // Bellman-ford
    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        FOREACH(it, g[cur]) {
            if(it->capacity - it->flow > 0) {
                const int nc = dist[cur]+it->cost;
                if(nc < dist[it->index]) {
                    dist[it->index] = nc;
                    parent[it->index] = make_pair(cur, distance(g[cur].begin(), it));
                    q.push(it->index);
                }
            }
        }
    }
    if (parent[sink].first == -1) {
      break;
    }

    Flow e = f;
    for (int i = sink; i != source; i = parent[i].first) {
        //cout << i << endl;
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

// [2*(r*C)+c] -> real
// [2*(r*C)+c+1] -> imag
vector<Edge> graph[MAXN];
const int INF = 100;

int N, K;
inline int node_of(int r, int c) {
    return r*N*2 + c*2;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;
    TIMES(r, N) {
        TIMES(c, N) {
            const int cur = node_of(r, c);
            int v;
            cin >> v;
            make_edge(graph, cur, cur+1, 1, -v);
            make_edge(graph, cur, cur+1, INF, 0);
            if(r+1 < N) {
                make_edge(graph, cur+1, node_of(r+1, c), INF, 0);
            }
            if(c+1 < N) {
                make_edge(graph, cur+1, node_of(r, c+1), INF, 0);
            }
        }
    }
    const int SRC = N*N*2;
    const int SINK = SRC+1;
    make_edge(graph, SRC, node_of(0, 0), INF, 0);
    make_edge(graph, node_of(N-1, N-1)+1, SINK, INF, 0);

    pair<int,int> res = primal_dual(graph, N*N*2+2, SRC, SINK, K);
    cout << -res.second << endl;
    return 0;
}
