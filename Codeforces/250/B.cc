//Name: The Child and Zoo
//Level: 4
//Category: グラフ,Graph,Union Find
//Note:

/**
 * 条件は
 * ・pからqへの経路のコストを、経路中にある一番安い頂点のコストとする。
 * ・このとき、一番高いコストの経路をf(p,q)とする。
 * この条件下では、頂点ではなく、辺に安い方の頂点と同じコストが割り当てられていると見て良い。
 * このとき、一番高いコストの経路が欲しいことから、高いほうの辺から追加していって、
 * 接続された頂点間では、f(p,q)はその辺のコストとなる。
 *
 * 接続された頂点どうしは同一視してよいので、Union Findによって、高い方の辺から追加していって
 * 接続状態を管理しつつ、接続された頂点集合どうしでf(p,q)がどれだけ増えるかを見れば良い。
 *
 * オーダーは O(M log M)。
 */
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;

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

struct Tag {
    int cost;
    int a, b;

    bool operator <(const Tag &other) const {
        return cost < other.cost;
    }
};

bool solve() {
    int N, M;
    if(!(cin >> N >> M)) return false;
    vector<int> vs(N);
    vector<Tag> edges;
    for(int i = 0; i < N; ++i) {
        cin >> vs[i];
    }
    for(int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        edges.push_back(Tag{min(vs[a], vs[b]), a, b});
    }
    sort(edges.begin(), edges.end());
    reverse(edges.begin(), edges.end());

    DisjointSet ds(N);
    double res = 0;
    for(auto e : edges) {
        if(ds.find(e.a, e.b)) continue;
        res += 2.0 * e.cost * ds.size(e.a) * ds.size(e.b);
        ds.unite(e.a, e.b);
    }
    res /= N;
    res /= N-1;
    printf("%.10f\n", res);
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
