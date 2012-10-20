/*
 * 市と市をつなぐのは単一の頂点であることが条件から保証されている．
 * したがってそれぞれの市ごとに全域木を求めれば，それが全体でも全域木となる．
 *
 * ひとつの市には最大7頂点しかないため，辺の数は最大でも 7*6/2 = 21．
 * ここから辺数 N-1 のセットを全て列挙し，Union-Find で全域木になっているもののみを選んで
 * コストを記憶しておく．
 *
 * 全体のコストは最大でも 77*6*77 = 35574 なので，それぞれのコストを作るパターン数をDPで求める．
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int INF = 50000;

struct Edge {
    int from, to, cost;

    Edge(int f, int t, int c) : from(f), to(t), cost(c) {}
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

void calc(const vector<Edge> &edges, const set<int> &towns, int T, vector<int> &costs) {
    const int E = edges.size();
    const int N = towns.size();
    for(int pat = 0; pat < (1<<E); ++pat) {
        if(__builtin_popcount(pat) != N-1) continue;
        DisjointSet ds(T);
        int cost = 0;
        for(int i = 0; i < E; ++i) {
            if(pat & (1<<i)) {
                ds.unite(edges[i].from, edges[i].to);
                cost += edges[i].cost;
            }
        }
        bool ok = true;
        int first = *towns.begin();
        for(set<int>::const_iterator it = towns.begin(); it != towns.end(); ++it) {
            if(ds.root(*it) != ds.root(first)) {
                ok = false;
                break;
            }
        }
        if(ok) {
            costs[cost]++;
            //cout << cost << endl;
        }
    }
}

int dp[2][40000];
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int A, T, K;
    cin >> A >> T >> K;
    vector<set<int> > cities(A);
    for(int i = 0; i < A; ++i) {
        int N;
        cin >> N;
        while(N--) {
            int C;
            cin >> C;
            cities[i].insert(C-1);
        }
    }
    vector<vector<Edge> > edges(A);
    int sum = 0;
    int M;
    cin >> M;
    while(M--) {
        int c1, c2, cost;
        cin >> c1 >> c2 >> cost;
        --c1; --c2;
        for(int i = 0; i < A; ++i) {
            if(cities[i].count(c1) && cities[i].count(c2)) {
                edges[i].push_back(Edge(c1, c2, cost));
            }
        }
        sum += cost;
    }
    vector<vector<int> > costs(A, vector<int>(500, 0));
    for(int i = 0; i < A; ++i) {
        calc(edges[i], cities[i], T, costs[i]);
    }
    dp[1][0] = 1;
    for(int i = 0; i < A; ++i) {
        const int cur = i&1;
        const int prev = cur^1;
        const vector<int> &cv = costs[i];
        for(int cost = 0; cost < 40000; ++cost) dp[cur][cost] = 0;
        for(int cost = 0; cost < 40000; ++cost) {
            if(dp[prev][cost] > 0) {
                for(int adc = 0; adc < 500; ++adc) {
                    if(cv[adc] != 0 && cost+adc < 40000) dp[cur][cost+adc] += dp[prev][cost]*cv[adc];
                    if(dp[cur][cost+adc] > K) dp[cur][cost+adc] = K;
                }
            }
        }
    }
    int acc = 0;
    int ans = -1;
    for(int cost = 40000-1; cost >= 0; --cost) {
        acc += dp[(A+1)&1][cost];
        if(acc >= K) {
            ans = sum-cost;
            break;
        }
    }
    cout << ans << endl;
    return 0;
}
