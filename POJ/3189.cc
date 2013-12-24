//Name: Steady Cow Assignment
//Level: 3
//Category: グラフ,Graph,最大流,Maximum flow
//Note:

/**
 * ランキングの中で使える範囲を決めた時、それぞれの牛からBarnへのグラフを作り、流量Nを流せればよい。
 * 区間の長さについては二分探索を使うことで高速化できる。
 *
 * オーダーはO((N+B)^2 NB log B)。
 * ただし最大流にDinicを使うと高速なので間に合う(C++で1000MS)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

const int M = 1100;
const int INF = 10000;

int ranking[1000][20];
int capacity[20];

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

// O(V^2 E)
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

bool solve() {
    int N, B;
    if(scanf("%d %d", &N, &B) == EOF) return false;
    if(!N && !B) return false;
    TIMES(i, N) {
        TIMES(j, B) {
            scanf("%d", &ranking[i][j]);
            --ranking[i][j];
        }
    }
    TIMES(i, B) {
        scanf("%d", &capacity[i]);
        if(capacity[i] > N) capacity[i] = N;
    }
    const int SRC = N+B;
    const int SINK = SRC+1;
    int l = -1, r = B-1;
    while(l+1 < r) {
        const int w = (l+r) / 2;
        int cap[M][M] = {0};
        TIMES(i, B) {
            cap[N+i][SINK] = capacity[i];
        }
        TIMES(i, N) {
            cap[SRC][i] = 1;
        }
        bool ok = false;
        TIMES(h, B-w) {
            if(h > 0) {
                TIMES(i, N) {
                    cap[i][N+ranking[i][h-1]] = 0;
                }
            }
            for(int rank = h; rank <= h+w; ++rank) {
                TIMES(i, N) {
                    cap[i][N+ranking[i][rank]] = 1;
                }
            }
            if(dinic(cap, N+B+2, SRC, SINK) == N) {
                ok = true;
                break;
            }
        }
        if(ok) r = w;
        else l = w;
    }
    printf("%d\n", r+1);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
