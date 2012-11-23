//Name: Perfect Service
//Level: 4
//Category: グラフ,Graph,木,二部グラフ,最小頂点被覆
//Note:

/*
 * 木は二部グラフになるので，この最小頂点被覆は二部マッチングで求められ，
 * またこのときの被覆は条件(every client is served by exactly one server)を満たしている．
 *
 * オーダーは O(N^2) だが，二部マッチングは一般に最悪オーダーよりずっと速い．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void paint(int N, int c, const vector<vector<int> > &graph, vector<int> &color) {
    color[N] = c;
    for(vector<int>::const_iterator it = graph[N].begin(); it != graph[N].end(); ++it) {
        if(color[*it] == -1) paint(*it, 1-c, graph, color);
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
int bipartite_matching(const vector<vector<int> >& g)
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
    while(true) {
        int N;
        cin >> N;
        if(N == -1) break;
        vector<pair<int,int> > input;
        vector<vector<int> > graph(N);
        for(int i = 0; i < N-1; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            graph[a].push_back(b);
            graph[b].push_back(a);
            input.push_back(make_pair(a, b));
        }
        int last;
        cin >> last;

        vector<int> color(N, -1);
        paint(0, 0, graph, color);

        vector<vector<int> > bgraph(N);
        for(vector<pair<int,int> >::iterator it = input.begin(); it != input.end(); ++it) {
                if(color[it->first] == 0) bgraph[it->first].push_back(it->second);
                else bgraph[it->second].push_back(it->first);
        }
        int res = bipartite_matching(bgraph);
        cout << res << endl;
        if(last == -1) break;
    }
}
