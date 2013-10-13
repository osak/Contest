//Name: グラフ
//Level: 3
//Category: グラフ,Graph,強連結成分分解,最小費用流
//Note:

/**
 * 同じ頂点を複数回通ってもいいので、強連結成分は縮約して、DAG上で考えることができる。
 * DAG上でN本のパスを使ってなるべく多くの頂点を被覆する問題は、
 *   [a]->[b]
 * のような辺を
 *   [a]-(0/∞)->[c]
 *   [c]-(-v/1)->[b]
 *   [c]-(0/∞)->[b]
 * の3辺に分解し、最小費用流を求めることで解ける。
 * ここで、辺 [a]-(v/f)->[b] は、ab間にあるコストv、容量fの辺を表す。
 * (DAGであることから負閉路は形成されない)
 *
 * オーダーは O(N^3)。
 * これは最小費用流を求める際に使っているBellman-fordの計算量である。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

const int INF = 1000000;

struct Edge {
    int a, b;
    int cost, cap;
    int flow;
    Edge *back;

    Edge() {}
    Edge(int a, int b, int c, int cap) : a(a), b(b), cost(c), cap(cap), flow(0) {}
};

void scc_visit(const vector<vector<int> >& g, int v, vector<int>& scc_map, int& scc_size,/*{{{*/
        stack<int>& stk, vector<bool>& in_stk, vector<int>& low, vector<int>& num, int& time)
{
  low[v] = num[v] = ++time;
  stk.push(v);
  in_stk[v] = true;
  for (vector<int>::const_iterator it(g[v].begin()); it != g[v].end(); ++it) {
    const int u = *it;
    if (num[u] == 0) {
      scc_visit(g, u, scc_map, scc_size, stk, in_stk, low, num, time);
      low[v] = min(low[v], low[u]);
    } else if (in_stk[u]) {
      low[v] = min(low[v], num[u]);
    }
  }
  if (low[v] == num[v]) {
    for (;;) {
      const int u = stk.top();
      stk.pop();
      in_stk[u] = false;
      scc_map[u] = scc_size;
      if (u == v) {
        break;
      }
    }
    ++scc_size;
  }
}/*}}}*/

// O(V+E)
pair<vector<int>,int> strongly_connected_components(const vector<vector<int> >& g)/*{{{*/
{
  const int N = g.size();
  vector<int> num(N), low(N);
  stack<int> stk;
  vector<bool> in_stk(N, false);
  int time = 0;
  vector<int> scc_map(N);
  int scc_size = 0;
  for (int v = 0; v < N; v++) {
    if (num[v] == 0) {
      scc_visit(g, v, scc_map, scc_size, stk, in_stk, low, num, time);
    }
  }
  return make_pair(scc_map, scc_size);
}/*}}}*/

void make_edge(int a, int b, int cost, int cap, vector<Edge*> &edges) {
    Edge *ae = new Edge(a, b, cost, cap);
    Edge *be = new Edge(b, a, -cost, 0);
    ae->back = be;
    be->back = ae;
    edges.push_back(ae);
    edges.push_back(be);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;

    const int SOURCE = N;
    vector<vector<int>> graph(N+1);
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            int v;
            cin >> v;
            if(v) graph[i].push_back(j);
        }
        graph[SOURCE].push_back(i);
    }

    auto res = strongly_connected_components(graph);
    const int M = res.second;
    vector<vector<int>> graph_scc(M);
    for(int i = 0; i < N+1; ++i) {
        const int scc_i = res.first[i];
        for(auto neigh : graph[i]) {
            const int scc_n = res.first[neigh];
            if(scc_i != scc_n) graph_scc[scc_i].push_back(scc_n);
        }
    }
    for(auto &row : graph_scc) {
        sort(row.begin(), row.end());
        row.erase(unique(row.begin(), row.end()), row.end());
    }
    const int SCC_SOURCE = res.first[SOURCE];

    // extend the graph
    vector<int> value(M, 0);
    for(auto i : res.first) {
        value[i]++;
    }
    value[SCC_SOURCE] = 0;
    vector<Edge*> edges;
    for(int i = 0; i < M; ++i) {
        const int dup_i = M+i;
        make_edge(dup_i, i, 0, INF, edges);
        make_edge(dup_i, i, -value[i], 1, edges);
    }
    for(int i = 0; i < M; ++i) {
        for(auto j : graph_scc[i]) {
            const int dup_j = M+j;
            make_edge(i, dup_j, 0, INF, edges);
        }
    }
    const int E = edges.size();
    /*
    for(auto &e : edges) {
        cout << e.a << ' ' << e.b << ' ' << e.cost << endl;
    }
    */

    // Minimum cost flow
    int ans = 0;
    for(int _ = 0; _ < 2; ++_) {
        vector<int> dp(M*2, INF);
        vector<Edge*> prev(M*2, NULL);
        dp[SCC_SOURCE] = 0;
        bool changed = true;
        while(changed) {
            changed = false;
            for(int i = 0; i < E; ++i) {
                Edge *e = edges[i];
                if(e->cap - e->flow == 0) continue;
                if(dp[e->a] == INF) continue;
                const int nc = dp[e->a] + e->cost;
                if(nc < dp[e->b]) {
                    dp[e->b] = nc;
                    prev[e->b] = e;
                    changed = true;
                }
            }
        }
        const int min_idx = distance(dp.begin(), min_element(dp.begin(), dp.end()));
        ans += -dp[min_idx];
        int cur = min_idx;
        while(prev[cur]) {
            prev[cur]->flow++;
            prev[cur]->back->flow--;
            cur = prev[cur]->a;
        }
    }
    cout << ans << endl;
    return 0;
}
