//Name: marukaite
//Level: 4
//Category: 最小費用流,minimum cost flow
//Note:

/*
 * 列に対応するノードをN個，行に対応するノードをN個それぞれ用意し，これらの間に容量1の辺を張る．
 * コストはある行rについて，ある列cだけをo，他を.にするときにかかるコストとする．
 */
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <string>
#include <limits>

using namespace std;

struct Edge {
    int index, capacity, cost;
    Edge(int i, int c, int d) : index(i), capacity(c), cost(d) {}
};

struct Command {
    int r, c;
    string cmd;
    Command(int r, int c, const string &cmd) : r(r), c(c), cmd(cmd) {}
};

// O(V^2 U C) where
//  U = sum of capacity
//  C = sum of cost
pair<int,int> primal_dual(const vector<vector<Edge> >& g, int source, int sink, int total_flow, vector<vector<int> > &flow)/*{{{*/
{
  const int N = g.size();
  vector<vector<int> > capacity(N, vector<int>(N, 0)), cost(N, vector<int>(N, 0)); 
  flow = vector<vector<int> >(N, vector<int>(N, 0));
  for (int i = 0; i < N; i++) {
    for (vector<Edge>::const_iterator it(g[i].begin()); it != g[i].end(); ++it) {
      capacity[i][it->index] = it->capacity;
      cost[i][it->index] = it->cost;
    }
  }
  pair<int,int> total;  // (cost, flow)
  vector<int> h(N, 0);
  for (int f = total_flow; f > 0; ) {
    vector<int> dist(N, 1000000);
    dist[source] = 0;
    vector<int> parent(N, -1);
    priority_queue<pair<int,int> > q;
    q.push(make_pair(0, source));
    while (!q.empty()) {
      const int n = q.top().second;
      const int c = -q.top().first;
      q.pop();
      for (vector<Edge>::const_iterator it(g[n].begin()); it != g[n].end(); ++it) {
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

int write_cost[128][128];
int erase_cost[128][128];
char field[128][128];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int N;
    cin >> N;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> write_cost[i][j];
        }
    }
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> erase_cost[i][j];
        }
    }
    for(int i = 0; i < N; ++i) {
        cin >> &field[i][0];
    }

    // 0..N-1: Row
    // N..2N-1: Col
    // 2N: Source
    // 2N+1: Sink
    vector<vector<Edge> > graph(2*N+2);
    for(int r = 0; r < N; ++r) {
        int sum = 0;
        for(int c = 0; c < N; ++c) {
            if(field[r][c] == 'o') sum += erase_cost[r][c];
        }
        for(int c = 0; c < N; ++c) {
            int cost = sum;
            if(field[r][c] == 'o') cost -= erase_cost[r][c];
            else cost += write_cost[r][c];
            graph[r].push_back(Edge(N+c, 1, cost));
            graph[N+c].push_back(Edge(r, 0, -cost));
        }
    }
    for(int r = 0; r < N; ++r) {
        graph[2*N].push_back(Edge(r, 1, 0));
    }
    for(int c = 0; c < N; ++c) {
        graph[N+c].push_back(Edge(2*N+1, 1, 0));
    }
    vector<vector<int> > flow;
    pair<int,int> result = primal_dual(graph, 2*N, 2*N+1, N, flow);
    vector<Command> commands;
    for(int r = 0; r < N; ++r) {
        for(int c = 0; c < N; ++c) {
            if(field[r][c] == 'o' && flow[r][N+c] == 0)
                commands.push_back(Command(r+1, c+1, "erase"));
            else if(field[r][c] == '.' && flow[r][N+c] > 0)
                commands.push_back(Command(r+1, c+1, "write"));
        }
    }
    cout << result.first << endl;
    cout << commands.size() << endl;
    for(vector<Command>::const_iterator it = commands.begin(); it != commands.end(); ++it) {
        cout << it->r << ' ' << it->c << ' ' << it->cmd << endl;
    }
    return 0;
}

