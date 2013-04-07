//Name: Dining
//Level: 3
//Category: グラフ,Graph,最大流
//Note:

/*
 * S - 食べ物 - 牛1 - 牛2 - 飲み物 - T
 * という形のグラフを作って最大流を求める．
 * ただし牛1と牛2はどちらもN頂点づつで，同じ牛の間のみに辺を張る（逆流防止）．
 *
 * オーダーはDinicのO(N^2 E)．
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

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define TIMES(__i, __n) for(int __i = 0; __i < __n; ++__i)

typedef vector<int> GraphRow;
typedef vector<GraphRow> Graph;
const int M = 402;
const int INF = 1000;

template <class T>
T dinic_augment(const Graph &g, int N, T flow[M][M], int level[M], bool finished[M], int u, int sink, T cur)/*{{{*/
{
  if (u == sink || cur == 0) {
    return cur;
  }
  if (finished[u]) {
    return 0;
  }
  finished[u] = true;
  for (int v = 0; v < N; v++) {
    if (g[u][v] - flow[u][v] > 0 && level[v] > level[u]) {
      const T f = dinic_augment(g, N, flow, level, finished, v, sink, min(cur, g[u][v] - flow[u][v]));
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

// O(V^2 E)
template <typename T>
T dinic(const Graph &g, int N, int source, int sink)/*{{{*/
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
                if (level[v] < 0 && g[u][v] - flow[u][v] > 0) {
                    q.push(v);
                    level[v] = level[u] + 1;
                }
            }
        }

        static bool finished[M];
        fill_n(finished, M, false);
        bool updated = false;
        while (true) {
            const T f = dinic_augment(g, N, flow, level, finished, source, sink, INF);
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

inline int cow1(int idx, int N, int F, int D) {
    return idx;
}

inline int cow2(int idx, int N, int F, int D) {
    return N+idx;
}

inline int food(int idx, int N, int F, int D) {
    return N*2+idx;
}

inline int drink(int idx, int N, int F, int D) {
    return N*2+F+idx;
}

inline int source(int N, int F, int D) {
    return N*2+F+D;
}

inline int sink(int N, int F, int D) {
    return source(N, F, D)+1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, F, D;
    while(cin >> N >> F >> D) {
        Graph graph(F+N*2+D+2, GraphRow(F+N*2+D+2));
        TIMES(ci, N) {
            int nf, nd;
            cin >> nf >> nd;
            TIMES(_, nf) {
                int fi;
                cin >> fi;
                --fi;
                graph[food(fi, N, F, D)][cow1(ci, N, F, D)] = 1;
                graph[source(N, F, D)][food(fi, N, F, D)] = 1;
            }
            TIMES(_, nd) {
                int di;
                cin >> di;
                --di;
                graph[cow2(ci, N, F, D)][drink(di, N, F, D)] = 1;
                graph[drink(di, N, F, D)][sink(N, F, D)] = 1;
            }
            graph[cow1(ci, N, F, D)][cow2(ci, N, F, D)] = 1;
        }
        cout << dinic<int>(graph, graph.size(), source(N, F, D), sink(N, F, D)) << endl;
    }
    return 0;
}
