//Name: School Excursion
//Level: 4
//Category: 最小費用流,強実装
//Note:

/*
 * 条件を整理すると，
 * ・なるべく多くのグループをゴールにたどり着かせる
 * ・そのときのコストを最小にする
 * ・あるノードから出るエッジは，高々1グループのみが使える
 * となる．
 * これは駅のノードを到着と出発に分割して管理することで最小費用流に落としこめる．
 * 具体的には
 * ・出発ノード間の移動は ∞/0(以下，エッジを 容量/コスト で表記する)
 * ・出発ノードから次の駅の到着ノード間の移動は 1/c_ij
 * ・到着ノードからその駅の出発ノード間の移動は 1/0
 *   ただし，到着ノードより早い時刻の出発ノードには行けない
 * ・ソースからは最初の駅の出発ノードに直接 ∞/0 のエッジを張る(サンプルから，出発時は同じ駅に複数グループがいてよいことが分かる)
 * ・最後の駅の各到着ノードからシンクに直接 1/0 のエッジを張る
 * とすればよい．
 *
 * オーダーは前処理に O(NM^2) (到着ノード等を探すのに線形探索しているため)，
 * 最小費用流は Primal-dual を用いて O(V^2 U C) = O(N^2 M^2)．
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Tag {
    int depart, arrive, cost;
};

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
void make_edge(vector<vector<edge<Flow, Cost> > > &g, int src, int dst, Flow c, Cost d)/*{{{*/
{
  const int i = g[src].size(), j = g[dst].size();
  g[src].push_back(edge<Flow, Cost>(dst, c, d, j));
  g[dst].push_back(edge<Flow, Cost>(src, 0, -d, i));
}/*}}}*/

const int MAXN = 100*40+10;

// O(V^2 U C) where
//  U = sum of capacity
//  C = sum of cost
template <class Flow, class Cost>
pair<Flow, Cost>
primal_dual(vector<vector<edge<Flow, Cost> > > &g, int N, int source, int sink, int max_flow)/*{{{*/
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

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<vector<int> > arrive_times(N), depart_times(N);
        vector<vector<Tag> > trains(N-1);
        for(int i = 0; i < N-1; ++i) {
            int M;
            cin >> M;
            for(int j = 0; j < M; ++j) {
                Tag t;
                cin >> t.depart >> t.arrive >> t.cost;
                trains[i].push_back(t);
                arrive_times[i+1].push_back(t.arrive);
                depart_times[i].push_back(t.depart);
            }
        }
        int G;
        cin >> G;

        // Make graph
        // graph[n*40..n*40+19] = arrival node of station n
        // graph[n*40+20..n*40+39] = departural node of station n
        // graph[N*40] = Source
        // graph[N*40+1] = Sink
        vector<vector<edge<int,int> > > graph(N*40+2);
        for(int i = 0; i < N-1; ++i) {
            const vector<Tag> &v = trains[i];
            vector<int> &dv = depart_times[i];
            vector<int> &av = arrive_times[i+1];
            sort(dv.begin(), dv.end());
            dv.erase(unique(dv.begin(), dv.end()), dv.end());
            sort(av.begin(), av.end());
            av.erase(unique(av.begin(), av.end()), av.end());
            // 駅iから駅i+1への移動
            for(vector<Tag>::const_iterator it = v.begin(); it != v.end(); ++it) {
                int dep_node = i*40+20 + (find(dv.begin(), dv.end(), it->depart) - dv.begin());
                int arrive_node = (i+1)*40 + (find(av.begin(), av.end(), it->arrive) - av.begin());
                make_edge(graph, dep_node, arrive_node, 1, it->cost);
            }
            if(i > 0) {
                // 駅i到着から駅i出発の移動
                const vector<int> &iav = arrive_times[i];
                for(int j = 0; j < (int)iav.size(); ++j) {
                    int arrive_node = i*40 + j;
                    int dep_node = i*40+20 + (lower_bound(dv.begin(), dv.end(), iav[j]) - dv.begin());
                    if(dep_node <= i*40+39) make_edge(graph, arrive_node, dep_node, 1, 0);
                }
                // 出発ノード間の移動
                for(int j = 0; j < (int)(dv.size()-1); ++j) {
                    int dep_node = i*40+20 + j;
                    int next_node = dep_node + 1;
                    make_edge(graph, dep_node, next_node, G, 0);
                }
            }
        }
        // Source
        // 駅0出発の各ノードに張る．
        {
            const vector<int> &dv = depart_times[0];
            const int SOURCE = N*40;
            for(int i = 0; i < (int)dv.size(); ++i) {
                int dep_node = 0*40+20 + i;
                make_edge(graph, SOURCE, dep_node, G, 0);
            }
        }
        // Sink
        // 駅(N-1)到着の各ノードに張る．
        {
            const vector<int> &av = arrive_times[N-1];
            const int SINK = N*40+1;
            for(int i = 0; i < (int)av.size(); ++i) {
                int arrive_node = (N-1)*40 + i;
                make_edge(graph, arrive_node, SINK, 1, 0);
            }
        }
        pair<int,int> res = primal_dual(graph, N*40+2, N*40, N*40+1, G);
        cout << res.first << ' ' << res.second << endl;
    }
    return 0;
}
