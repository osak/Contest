//Name: Stellar Performance of the Debunkey Family
//Level: 2
//Category: グラフ,Graph,最小全域木,Minimum Spanning Tree,MST
//Note:

/*
 * 最小全域木を求めればよい。
 *
 * このコードではKruskal法を用いている。
 * オーダーは O(M log M)。
 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Edge {
    int a, b, c;

    bool operator <(const Edge &e) const {
        return c < e.c;
    }
};

struct DisjointSet/*{{{*/
{
  vector<int> parent;

  int root(int x)
  {
    if (parent[x] < 0) {
      return x;
    } else {
      parent[x] = root(parent[x]);
      return parent[x];
    }
  }

  explicit DisjointSet(int n) : parent(n, -1) {}

  bool unite(int x, int y)
  {
    const int a = root(x);
    const int b = root(y);
    if (a != b) {
      if (parent[a] < parent[b]) {
        parent[a] += parent[b];
        parent[b] = a;
      } else {
        parent[b] += parent[a];
        parent[a] = b;
      }
      return true;
    } else {
      return false;
    }
  }

  bool find(int x, int y) { return root(x) == root(y); }
  int size(int x) { return -parent[root(x)]; }
};/*}}}*/

bool solve() {
    int N, M;
    if(!(cin >> N >> M)) return false;
    if(!N && !M) return false;

    vector<Edge> edges(M);
    for(int i = 0; i < M; ++i) {
        Edge &e = edges[i];
        cin >> e.a >> e.b >> e.c;
    }
    sort(begin(edges), end(edges));

    DisjointSet ds(N);
    int ans = 0;
    for(const auto &e : edges) {
        if(ds.unite(e.a, e.b)) {
            ans += e.c;
        }
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    while(solve()) ;
    return 0;
}
