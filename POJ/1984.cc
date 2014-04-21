//Name: Navigation Nightmare
//Level: 3
//Category: グラフ,Graph,木,Tree,LCA,Lowest Common Ancestor
//Note:

/**
 * 辺のコストを向きに応じた二次元値にして、適当なノードを根とした木に変形する。
 * ノードaとノードbの間のマンハッタン距離は、a→LCA(a,b)→bの順で訪問したときのコスト和と等しい。
 * （コストの符号は、辺を登る時は正、下りるときは負になることに注意）
 *
 * また、辺が途中まで与えられた状態でマンハッタン距離が求められるかどうかは、クエリの2頂点を結ぶ
 * パスが存在しているかどうかで判定できる。
 * これはUnion-Findによって管理できる。
 * （先に完全な木を構築してしまい、-1の判定はクエリを時刻でソートして後付けでやればよい）
 *
 * オーダーはO(K log M)。
 */
#include <cstdio>
#include <queue>
#include <vector>
#include <complex>
#include <list>
#include <algorithm>

using namespace std;

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

typedef long long LL;
typedef complex<LL> Distance;

struct Edge {
    int a, b;
    Distance d;

    Edge() : a(-1), b(0) {}
    Edge(int a, int b, const Distance &d) : a(a), b(b), d(d) {}
};

pair<int,int> edge_q[40010];
list<Edge> edges[40010];
pair<pair<int,int>,pair<int,int> > queries[10010];
LL answers[10010];

Distance make_dist(char dir, LL len) {
    switch(dir) {
    case 'N':
        return Distance(0, -len);
    case 'E':
        return Distance(len, 0);
    case 'S':
        return Distance(0, len);
    case 'W':
        return Distance(-len, 0);
    }
    return Distance();
}

void add_edge(int a, int b, const Distance &d) {
    edges[a].push_front(Edge(a, b, d));
    edges[b].push_front(Edge(b, a, -d));
}

pair<int,Distance> ancestor[40010][16];
int depth[40010];

void make_tree(int v, const Edge &e, int d) {
    depth[v] = d;
    int cur = e.a;
    Distance dist = e.d;
    for(int level = 0; cur != -1; cur = ancestor[cur][level++].first) {
        ancestor[v][level] = make_pair(cur, dist);
        dist += ancestor[cur][level].second;
    }
    list<Edge>::const_iterator end = edges[v].end();
    for(list<Edge>::const_iterator it = edges[v].begin(); it != end; ++it) {
        if(depth[it->b] != -1) continue;
        make_tree(it->b, *it, d+1);
    }
}

bool solve() {
    int N, M;
    if(scanf("%d %d", &N, &M) == EOF) return false;
    if(!N && !M) return false;

    for(int i = 0; i < N; ++i) {
        edges[i].clear();
        depth[i] = -1;
        for(int j = 0; j < 16; ++j) {
            ancestor[i][j] = make_pair(-1, Distance());
        }
    }
    for(int i = 0; i < M; ++i) {
        int a, b, l;
        char dir;
        scanf("%d %d %d %c", &a, &b, &l, &dir);
        --a; --b;
        add_edge(a, b, make_dist(dir, l));
        edge_q[i] = make_pair(a, b);
    }

    make_tree(0, Edge(), 0);

    DisjointSet ds(N);
    int K;
    scanf("%d", &K);
    for(int i = 0; i < K; ++i) {
        int from, to, t;
        scanf("%d %d %d", &from, &to, &t);
        --from; --to;
        queries[i] = make_pair(make_pair(t, i), make_pair(from, to));
    }
    sort(queries, queries+K);
    for(int k = 0; k < K; ++k) {
        const int from = queries[k].second.first;
        const int to = queries[k].second.second;
        for(int t = k > 0 ? queries[k-1].first.first : 0; t < queries[k].first.first; ++t) {
            ds.unite(edge_q[t].first, edge_q[t].second);
        }
        if(ds.find(from, to)) {
            int deeper = depth[from] < depth[to] ? to : from;
            int shallower = depth[from] < depth[to] ? from : to;
            Distance dd, ds;
            {
                int diff = depth[deeper] - depth[shallower];
                for(int i = 0; i < 16; ++i) {
                    if(diff & (1<<i)) {
                        dd += ancestor[deeper][i].second;
                        deeper = ancestor[deeper][i].first;
                    }
                }
            }
            int left = -1, right = N;
            while(left+1 < right) {
                const int l = (left + right) / 2;
                int d = deeper, s = shallower;
                for(int i = 0; i < 16; ++i) {
                    if(l & (1<<i)) {
                        d = ancestor[d][i].first;
                        s = ancestor[s][i].first;
                        if(d == -1 || s == -1) {
                            break;
                        }
                    }
                }
                if(d == -1 || s == -1 || d == s) {
                    right = l;
                } else {
                    left = l;
                }
            }
            //printf("%d\n", right);
            for(int i = 0; i < 16; ++i) {
                if(right & (1<<i)) {
                    dd += ancestor[deeper][i].second;
                    deeper = ancestor[deeper][i].first;
                    ds += ancestor[shallower][i].second;
                    shallower = ancestor[shallower][i].first;
                }
            }
            //printf("%lld %lld\n", dd.real(), dd.imag());
            //printf("%lld %lld\n", ds.real(), ds.imag());
            const Distance d = dd - ds;
            answers[queries[k].first.second] = llabs(d.real()) + llabs(d.imag());
        } else {
            answers[queries[k].first.second] = -1;
        }
    }
    for(int i = 0; i < K; ++i) {
        printf("%lld\n", answers[i]);
    }
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
