//Name: World Islands
//Level: 3
//Category: グラフ,Graph,最小全域木,MST
//Note:

/*
 * 取り除く点を全て試しながらMSTを構築する．
 * Kruskal法では，N-2本の辺を取っても単一の全域木にならないことに注意．
 *
 * オーダーは O(N^2 log N)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

struct DisjointSet {
    vector<int> roots;
    DisjointSet(int size) : roots(size) {
        for(int i = 0; i < size; ++i) {
            roots[i] = i;
        }
    }

    int root(int n) {
        if(roots[n] == n) return n;
        return roots[n] = root(roots[n]);
    }

    bool unite(int a, int b) {
        a = root(a);
        b = root(b);
        if(a == b) return false;
        roots[a] = b;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        vector<pair<int,int> > v(N);
        for(int i = 0; i < N; ++i) {
            cin >> v[i].first >> v[i].second;
        }
        vector<pair<double,pair<int,int> > > edges;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < i; ++j) {
                const double len = hypot(v[i].first-v[j].first, v[i].second-v[j].second);
                edges.push_back(make_pair(len, make_pair(i, j)));
            }
        }
        sort(edges.begin(), edges.end());
        double ans = 1e50;
        for(int exclude = 0; exclude < N; ++exclude) {
            double cost = 0;
            DisjointSet ds(N);
            for(int i = 0; i < (int)edges.size(); ++i) {
                const double c = edges[i].first;
                const int a = edges[i].second.first;
                const int b = edges[i].second.second;
                if(a == exclude || b == exclude) continue;
                if(!ds.unite(a, b)) continue;
                cost += c;
            }
            ans = min(ans, cost);
        }
        printf("%.2f\n", ans);
    }
    return 0;
}
