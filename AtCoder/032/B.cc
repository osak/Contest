//Name: 道路工事
//Level: 2
//Category: グラフ,Graph,連結性
//Note: 

/**
 * 連結成分の個数が分かれば、これらを一直線に繋げればよい。
 * すなわち、(連結成分の個数-1)本の辺を追加すればよい。
 *
 * オーダーは O(M + N log N)。
 */
#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct DisjointSet {
    vector<int> parent;

    DisjointSet(size_t s) : parent(s, -1) {}

    int root(int u) {
        if(parent[u] < 0) return u;
        return parent[u] = root(parent[u]);
    }

    bool unite(int u, int v) {
        const int ru = root(u);
        const int rv = root(v);
        if(ru == rv) return false;
        if(size(ru) > size(rv)) {
            parent[ru] += parent[rv];
            parent[rv] = ru;
        } else {
            parent[rv] += parent[ru];
            parent[ru] = rv;
        }
        return true;
    }

    int size(int u) {
        return -parent[root(u)];
    }
};

bool solve(bool first) {
    int N, M;
    if(!(cin >> N >> M)) return false;
    if(!N && !M) return false;

    DisjointSet ds(N);
    for(int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        ds.unite(a, b);
    }

    set<int> s;
    for(int i = 0; i < N; ++i) {
        s.insert(ds.root(i));
    }
    cout << s.size()-1 << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
