//Name: Evacuation
//Level: 4
//Category: グラフ,Graph,二部マッチング
//Note:

/*
 * 同じマスに何人でも入れるので，ある人が特定のドアに到達する最短時間は容易に求まる．
 * ひとつのドアからは一度に一人しか脱出できないので，これは時間tにドアdiから出る人を決める最大マッチングとして定式化できる．
 * あとはtの最大値を二分探索する．
 *
 * オーダーは最悪で O(RC^4)程度(頂点数が左O(RC)，右O(RC)，辺数O(RC^2)とすると二部マッチングがO(RC^4))．
 * 実際には頂点数は少なく，完全二部グラフもあり得ないのでもっと楽観的なオーダーだが，
 * POJではこのコードで907msとギリギリだった．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define TIMES(__i,__n) for(int __i = 0; __i < __n; ++__i)

const int INF = 1000000;
int R, C;
int doorcnt;
inline int node(int r, int c) {
    return C*r + c;
}

inline int door(int idx, int turn) {
    return R*C + doorcnt*turn + idx;
}

void make_edge(vector<vector<int> > &graph, int dr, int dc, int di, const vector<vector<int> > &distmap, const int threshold) {
    const int doornode = node(dr, dc);
    TIMES(r, R) {
        TIMES(c, C) {
            const int n = node(r, c);
            if(distmap[n][doornode] != INF && distmap[n][doornode] <= threshold) {
                //cout << dr << ' ' << dc << ' ' << r << ' ' << c << ' ' << distmap[n][doornode] << endl;
                for(int turn = distmap[n][doornode]; turn <= threshold; ++turn) {
                    graph[n].push_back(door(di, turn));
                }
            }
        }
    }
}

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

// O(V(V+E))
// Ford Fulkersonの変形．
int bipartite_matching(const vector<vector<int> >& g, int L)  // {{{
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
  return match;
} // }}}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    while(N--) {
        cin >> R >> C;
        vector<string> field(R);
        TIMES(r, R) {
            cin >> field[r];
        }
        
        vector<vector<int> > distmap(R*C, vector<int>(R*C, INF));
        vector<pair<int,int> > doors;
        int mancnt = 0;
        TIMES(r, R) {
            TIMES(c, C) {
                static const int DR[] = {0, -1, 0, 1};
                static const int DC[] = {1, 0, -1, 0};
                if(field[r][c] == '.') {
                    TIMES(dir, 4) {
                        const int nr = r + DR[dir];
                        const int nc = c + DC[dir];
                        if(0 <= nr && nr < R && 0 <= nc && nc < C) {
                            if(field[nr][nc] != 'X') {
                                distmap[node(r, c)][node(nr, nc)] = 1;
                            }
                        }
                    }
                    distmap[node(r,c)][node(r,c)] = 0;
                }
                if(field[r][c] == 'D') doors.push_back(make_pair(r, c));
                else if(field[r][c] == '.') ++mancnt;
            }
        }
        doorcnt = doors.size();
        TIMES(k, R*C)
            TIMES(i, R*C)
                TIMES(j, R*C)
                    distmap[i][j] = min(distmap[i][j], distmap[i][k] + distmap[k][j]);

        vector<vector<int> > graph(mancnt + doorcnt*144);
        int left = -1, right = 144;
        bool found = false;
        while(left+1 < right) {
            int center = (left+right) / 2;
            FOREACH(it, graph) {
                it->clear();
            }
            TIMES(di, doorcnt) {
                make_edge(graph, doors[di].first, doors[di].second, di, distmap, center);
            }
            int match = bipartite_matching(graph, R*C);
            //cout << "lrm " << left << ' ' << right << ' ' << match << endl;
            if(match == mancnt) {
                right = center;
                found = true;
            } else {
                left = center;
            }
        }
        if(!found) cout << "impossible" << endl;
        else cout << right << endl;
    }
    return 0;
}
