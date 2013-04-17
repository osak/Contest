//Name: Muddy Fields
//Level: 3
//Category: グラフ,Graph,二部マッチング
//Note:

/*
 * 橋は可能な限り長く取って良い．
 * するとそれぞれの*は縦方向，横方向の橋でそれぞれ1回ずつカバーされる．
 * したがって，橋を頂点，*を辺とした二部グラフを構成して，最小被覆を最大マッチングで求めればよい．
 *
 * オーダーは O(R^2 C^2) 程度？
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
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

bool bm_augment(const vector<vector<int> >& g, int u, vector<int>& match_to, vector<unsigned char>& visited) // {{{
{
  if (u < 0) {
    return true;
  }

  for (vector<int>::const_iterator it(g[u].begin()); it != g[u].end(); ++it) {
    if (!visited[*it]) {
      visited[*it] = 1;
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
  for (int u = 0; u < L; u++) {
    vector<unsigned char> visited(N, 0);
    if (bm_augment(g, u, match_to, visited)) {
      match++;
    }
  }
  return match;
} // }}}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int R, C;
    while(cin >> R >> C) {
        vector<string> field(R);
        TIMES(i, R) {
            cin >> field[i];
        }

        vector<vector<pair<int,int> > > belongs(R, vector<pair<int,int> >(C));
        // Horizontal line
        int hlcnt = 0;
        TIMES(r, R) {
            for(int c = 0; c < C; ) {
                while(c < C && field[r][c] == '.') ++c;
                if(c == C) break;

                while(c < C && field[r][c] == '*') {
                    belongs[r][c].first = hlcnt;
                    ++c;
                }
                ++hlcnt;
            }
        }
        // Vertical line
        int vlcnt = 0;
        TIMES(c, C) {
            for(int r = 0; r < R; ) {
                while(r < R && field[r][c] == '.') ++r;
                if(r == R) break;
                
                while(r < R && field[r][c] == '*') {
                    belongs[r][c].second = vlcnt;
                    ++r;
                }
                ++vlcnt;
            }
        }
        vector<vector<int> > graph(hlcnt+vlcnt);
        TIMES(r, R) {
            TIMES(c, C) {
                if(field[r][c] == '*') {
                    graph[belongs[r][c].first].push_back(belongs[r][c].second+hlcnt);
                }
            }
        }
        cout << bipartite_matching(graph, hlcnt) << endl;
    }
    return 0;
}
