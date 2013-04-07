//Name: Minimum Cut
//Level: 3
//Category: グラフ,Graph,最小カット
//Note:

/*
 * 最小カットを求めるだけ．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <limits>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define TIMES(__i,__n) for(int __i = 0; __i < __n; ++__i)

// mininum cut
// O(V^3)
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

int main() {
    int N, M;
    while(scanf("%d %d", &N, &M) != EOF) {
        vector<vector<int> > graph(N, vector<int>(N, 0));
        TIMES(_, M) {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            graph[a][b] += c;
            graph[b][a] += c;
        }
        const int cost = stoer_wagner(graph);
        printf("%d\n", cost);
    }
    return 0;
}
