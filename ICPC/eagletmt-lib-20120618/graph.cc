#include <vector>
#include <queue>
#include <limits>
using namespace std;

template <typename T>
T edmonds_karp(const vector<vector<T> >& capacity, int source, int sink)/*{{{*/
{
  const int N = capacity.size();
  vector<vector<T> > flow(N, vector<T>(N, 0));
  T max_flow = 0;

  while (true) {
    vector<int> parent(N, -1);
    queue<int> q;
    q.push(source);

    while (!q.empty() && parent[sink] < 0) {
      const int v = q.front();
      q.pop();

      for (int u = 0; u < N; u++) {
        if (parent[u] < 0 && capacity[v][u] - flow[v][u] > 0) {
          parent[u] = v;
          if (u == sink) {
            break;
          }
          q.push(u);
        }
      }
    }

    if (parent[sink] < 0) {
      break;
    }

    T aug = numeric_limits<T>::max();
    for (int v = sink; v != source; v = parent[v]) {
      const int u = parent[v];
      aug = min(aug, capacity[u][v] - flow[u][v]);
    }
    max_flow += aug;
    for (int v = sink; v != source; v = parent[v]) {
      const int u = parent[v];
      flow[u][v] += aug;
      flow[v][u] -= aug;
    }
  }

  return max_flow;
}/*}}}*/

template <class T>
T dinic_augment(const T capacity[M][M], int N, T flow[M][M], int level[M], bool finished[M], int u, int sink, T cur)/*{{{*/
{
  if (u == sink || cur == 0) {
    return cur;
  }
  if (finished[u]) {
    return 0;
  }
  finished[u] = true;
  for (int v = 0; v < N; v++) {
    if (capacity[u][v] - flow[u][v] > 0 && level[v] > level[u]) {
      const T f = dinic_augment(capacity, N, flow, level, finished, v, sink, min(cur, capacity[u][v] - flow[u][v]));
      if (f > 0) {
        flow[u][v] += f;
        flow[v][u] -= f;
        finished[u] = false;
        return f;
      }
    }
  }
  return 0;
}/*}}}*/
template <typename T>
T dinic(const T capacity[M][M], int N, int source, int sink)/*{{{*/
{
  static T flow[M][M];
  for (int i = 0; i < N; i++) {
    fill_n(flow[i], N, 0);
  }
  T max_flow = 0;

  while (true) {
    static int level[M];
    fill_n(level, N, -1);
    level[source] = 0;
    queue<int> q;
    q.push(source);

    int d = N;
    while (!q.empty() && level[q.front()] < d) {
      const int u = q.front();
      q.pop();

      if (u == sink) {
        d = level[u];
      }
      for (int v = 0; v < N; v++) {
        if (level[v] < 0 && capacity[u][v] - flow[u][v] > 0) {
          q.push(v);
          level[v] = level[u] + 1;
        }
      }
    }

    static bool finished[M];
    fill_n(finished, M, false);
    bool updated = false;
    while (true) {
      const T f = dinic_augment(capacity, N, flow, level, finished, source, sink, INF);
      if (f == 0) {
        break;
      }
      max_flow += f;
      updated = true;
    }

    if (!updated) {
      break;
    }
  }

  return max_flow;
}/*}}}*/

// 連結な無向グラフのすべての辺を通るような閉路で，コストの合計の最小値
template <class T>
T chinese_postman(const vector<vector<pair<int,T> > >& g)/*{{{*/
{
  T total = 0;
  vector<int> odd_nodes;
  for (int i = 0; i < static_cast<int>(g.size()); i++) {
    for (vector<pair<int,T> >::const_iterator it(g[i].begin()); it != g[i].end(); ++it) {
      total += it->second;
    }
    if (g[i].size() % 2 == 1) {
      odd_nodes.push_back(i);
    }
  }
  total /= 2;

  const int N = odd_nodes.size();
  vector<vector<T> > w(N, vector<T>(N, -1));
  for (int i = 0; i < N; i++) {
    // dijkstra
    vector<T> dist(g.size(), 1000000);
    dist[odd_nodes[i]] = 0;
    priority_queue<pair<T,int> > q;
    q.push(make_pair(0, odd_nodes[i]));
    while (!q.empty()) {
      const T cost = -q.top().first;
      const int n = q.top().second;
      q.pop();
      for (vector<pair<int,T> >::const_iterator it(g[n].begin()); it != g[n].end(); ++it) {
        const T c = cost + it->second;
        if (c < dist[it->first]) {
          dist[it->first] = c;
          q.push(make_pair(-c, it->first));
        }
      }
    }
    for (int j = 0; j < N; j++) {
      w[i][j] = dist[odd_nodes[j]];
    }
  }

  vector<T> dp(1<<N, 1000000);
  dp[0] = 0;
  for (int s = 0; s < (1<<N); s++) {
    for (int i = 0; i < N; i++) {
      if (s & (1<<i)) {
        continue;
      }
      for (int j = i+1; j < N; j++) {
        if (s & (1<<j)) {
          continue;
        }
        dp[s | (1<<i) | (1<<j)] = min(dp[s | (1<<i) | (1<<j)], dp[s] + w[i][j]);
      }
    }
  }
  return total + dp[(1<<N)-1];
}/*}}}*/

bool bm_augment(const vector<vector<int> >& g, int u, vector<int>& match_to, vector<bool>& visited) // {{{
{
  if (u < 0) {
    return true;
  }

  for (vector<int>::const_iterator it(g[u].begin()); it != g[u].end(); ++it) {
    if (!visited[*it]) {
      visited[*it] = true;
      if (bm_augment(g, match_to[*it], match_to, visited)) {
        match_to[u] = *it;
        match_to[*it] = u;
        return true;
      }
    }
  }
  return false;
} // }}}

int bipartite_matching(const vector<vector<int> >& g, int L, vector<pair<int,int> >& matching)  // {{{
{
  const int N = g.size();
  vector<int> match_to(N, -1);
  int match = 0;
  for (int u = 0; u < N; u++) {
    vector<bool> visited(N, false);
    if (bm_augment(g, u, match_to, visited)) {
      match++;
    }
  }
  for (int u = 0; u < L; u++) {
    if (match_to[u] >= 0) {
      matching.push_back(make_pair(u, match_to[u]));
    }
  }
  return match;
} // }}}

// mininum cut
template <class T>
T stoer_wagner(vector<vector<T> > g)/*{{{*/
{
  const int N = g.size();
  vector<int> v(N);
  for (int i = 0; i < N; i++) {
    v[i] = i;
  }

  T cut = numeric_limits<T>::max();
  for (int m = N; m > 1; m--) {
    vector<T> ws(m, 0);
    int s, t = 0;
    T w;
    for (int k = 0; k < m; k++) {
      s = t;
      t = distance(ws.begin(), max_element(ws.begin(), ws.end()));
      w = ws[t];
      ws[t] = -1;
      for (int i = 0; i < m; i++) {
        if (ws[i] >= 0) {
          ws[i] += g[v[t]][v[i]];
        }
      }
    }
    for (int i = 0; i < m; i++) {
      g[v[i]][v[s]] += g[v[i]][v[t]];
      g[v[s]][v[i]] += g[v[t]][v[i]];
    }
    v.erase(v.begin() + t);
    cut = min(cut, w);
  }
  return cut;
}/*}}}*/

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

// minimum cost flow
// returns (cost, flow)
// POJ 2195
struct node/*{{{*/
{
  int index;
  int capacity;
  int cost;
  node(int i, int c, int d) : index(i), capacity(c), cost(d) {}
};/*}}}*/
pair<int,int> primal_dual(const vector<vector<node> >& g, int source, int sink)/*{{{*/
{
  const int N = g.size();
  vector<vector<int> > capacity(N, vector<int>(N, 0)), cost(N, vector<int>(N, 0)), flow(N, vector<int>(N, 0));
  for (int i = 0; i < N; i++) {
    for (vector<node>::const_iterator it(g[i].begin()); it != g[i].end(); ++it) {
      capacity[i][it->index] += it->capacity;
      cost[i][it->index] += it->cost;
    }
  }
  pair<int,int> total;  // (cost, flow)
  vector<int> h(N, 0);
  for (int f = numeric_limits<int>::max(); f > 0; ) {
    vector<int> dist(N, 1000000);
    dist[source] = 0;
    vector<int> parent(N, -1);
    priority_queue<pair<int,int> > q;
    q.push(make_pair(0, source));
    while (!q.empty()) {
      const int n = q.top().second;
      const int c = -q.top().first;
      q.pop();
      for (vector<node>::const_iterator it(g[n].begin()); it != g[n].end(); ++it) {
        if (capacity[n][it->index] - flow[n][it->index] > 0) {
          const int c2 = c + cost[n][it->index] + h[n] - h[it->index];
          if (c2 < dist[it->index]) {
            dist[it->index] = c2;
            parent[it->index] = n;
            q.push(make_pair(-c2, it->index));
          }
        }
      }
    }
    if (parent[sink] == -1) {
      break;
    }

    int e = f;
    for (int i = sink; i != source; i = parent[i]) {
      e = min(e, capacity[parent[i]][i] - flow[parent[i]][i]);
    }
    for (int i = sink; i != source; i = parent[i]) {
      total.first += e * cost[parent[i]][i];
      flow[parent[i]][i] += e;
      flow[i][parent[i]] -= e;
    }
    f -= e;
    total.second += e;
    for (int i = 0; i < N; i++) {
      h[i] += dist[i];
    }
  }
  return total;
}/*}}}*/

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
