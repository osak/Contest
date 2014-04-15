//Name: Median Tree
//Level: 2
//Category: グラフ,Graph,最小全域木,Minimum Spanning Tree
//Note:

/**
 * 普通に最小全域木を求め、そのときの中央値を求めればよい。
 *
 * MSTよりも中央値が小さくなる場合、MSTの中央値よりも小さいコストの辺iを追加することになるが、
 * MSTでその辺が選ばれていないということは、辺iよりもコストの小さい辺jによって辺iの両端点が連結になっているということである。
 * したがって、辺iを追加することで少なくとも辺jを取り除く必要が生じるため、中央値は変化しない。
 *
 * オーダーはO(M log M)。
 */
#include <iostream>
#include <vector>
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

struct Edge {
    int a, b;
    int cost;

    bool operator <(const Edge &other) const {
        return cost < other.cost;
    }
};

bool solve() {
    int N, M;
    if(!(cin >> N >> M)) return false;
    if(!N && !M) return false;

    vector<Edge> edges(M);
    for(int i = 0; i < M; ++i) {
        Edge &e = edges[i];
        cin >> e.a >> e.b >> e.cost;
        e.a--;
        e.b--;
    }
    sort(edges.begin(), edges.end());
    DisjointSet ds(N);
    int cnt = 0;
    for(Edge &e : edges) {
        if(ds.unite(e.a, e.b)) {
            ++cnt;
            if(cnt == N/2) {
                cout << e.cost << endl;
                break;
            }
        }
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
