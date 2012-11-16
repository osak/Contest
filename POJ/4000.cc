//Name: National Treasures
//Level: 4
//Category: グラフ,Graph,二部マッチング,最小被覆,Minimum Cover
//Note:

/*
 * critical points はマンハッタン距離が奇数の点にしかないため，宝と critical points を結ぶグラフは二部グラフになる．
 * 宝を取り除く個数を最小にして critical points を全て埋めたいのだから，この問題は最小被覆問題に帰着できる．
 * ここで，二部グラフの最小被覆は最大マッチングによって求めることができるから，単に最大マッチングを取れば良いことになる．
 *
 * オーダーは O(V^2)，ただし V = RC．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int DR[] = {-1, -2, -2, -1, 1, 2, 2, 1, -1, 0, 1, 0};
const int DC[] = {-2, -1, 1, 2, 2, 1, -1, -2, 0, 1, 0, -1};

int match_to[2500];
bool visited[2500];
bool bm_augment(const vector<vector<int> >& g, int u)
{
  if (u < 0) {
    return true;
  }

  for (vector<int>::const_iterator it(g[u].begin()); it != g[u].end(); ++it) {
    if (!visited[*it]) {
      visited[*it] = true;
      if (bm_augment(g, match_to[*it])) {
        match_to[u] = *it;
        match_to[*it] = u;
        return true;
      }
    }
  }
  return false;
}

// O(V(V+E))
// Ford Fulkersonの変形．
int bipartite_matching(const vector<vector<int> >& g)
{
  const int N = g.size();
  fill_n(match_to, N, -1);
  int match = 0;
  for (int u = 0; u < N; u++) {
      fill_n(visited, N, false);
      if (bm_augment(g, u)) {
          match++;
      }
  }
  return match;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for(int CASE = 1; ; ++CASE) {
        int R, C;
        cin >> R >> C;
        if(!R && !C) break;
        vector<vector<int> > field(R, vector<int>(C));
        for(int r = 0; r < R; ++r) {
            for(int c = 0; c < C; ++c) {
                cin >> field[r][c];
            }
        }
        vector<vector<int> > graph(R*C);
        for(int r = 0; r < R; ++r) {
            for(int c = 0; c < C; ++c) {
                if(field[r][c] == -1) continue;
                for(int b = 0; b < 12; ++b) {
                    if(field[r][c] & (1<<b)) {
                        const int nr = r + DR[b];
                        const int nc = c + DC[b];
                        if(nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                        if(field[nr][nc] == -1) continue;
                        const int n1 = r*C + c;
                        const int n2 = nr*C + nc;
                        if((r+c) % 2 == 0) {
                            graph[n1].push_back(n2);
                        } else {
                            graph[n2].push_back(n1);
                        }
                    }
                }
            }
        }
        cout << CASE << ". " << bipartite_matching(graph) << endl;
    }
    return 0;
}
