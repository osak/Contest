//Name: Asteroids
//Level: 4
//Category: グラフ,Graph,最小頂点被覆,二部マッチング
//Note:

/*
 * 列と行に対応するノードを作り，隕石(r,c)に対して辺(r,c)を張る．
 * すると全ての隕石を破壊する問題は，二部グラフの最小頂点被覆に帰着される．
 * したがって，最大マッチングの個数が答えとなる．
 *
 * オーダーは O(N(N+E))．
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
#define TIMES(__i,__n) for(int __i = 0; __i < __n; ++__i)

typedef vector<int> GraphRow;
typedef vector<GraphRow> Graph;

Graph g;
int to[1000];
bool visited[1000];

bool dfs(int pos) {
    if(pos == -1) return true;
    FOREACH(it, g[pos]) {
        if(!visited[*it]) {
            visited[*it] = true;
            if(dfs(to[*it])) {
                to[*it] = pos;
                to[pos] = *it;
                return true;
            }
        }
    }
    return false;
}

int bipartite_matching(int L) {
    const int N = g.size();
    fill_n(to, N, -1);
    int cnt = 0;
    TIMES(i, L) {
        fill_n(visited, N, false);
        if(dfs(i)) ++cnt;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, K;
    while(cin >> N >> K) {
        g.clear();
        g.resize(N*2);
        TIMES(_, K) {
            int R, C;
            cin >> R >> C;
            --R; --C;
            g[R].push_back(N+C);
        }
        int cnt = bipartite_matching(N);
        cout << cnt << endl;
    }
    return 0;
}
