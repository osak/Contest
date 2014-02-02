//Name: Kindergarten
//Level: 3
//Category: グラフ,Graph,二部マッチング,最大独立集合
//Note:

/**
 * 二部グラフ上で（左右それぞれの頂点間では互いに辺があるとして）クリークを求める問題になる。
 * これは補グラフ上で最大独立集合を求める問題と等しく、二部グラフ上の最大独立集合は
 * 頂点数から最大二部マッチングの個数を引いたもので求められる。
 *
 * オーダーはO(GM)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

vector<int> graph[200];
bool visited[200];
int match_to[200];

bool augment(int v) {
    if(v == -1) return true;
    if(visited[v]) return false;
    visited[v] = true;
    const int N = graph[v].size();
    TIMES(i, N) {
        if(augment(match_to[graph[v][i]])) {
            match_to[graph[v][i]] = v;
            return true;
        }
    }
    return false;
}

int bm(int N) {
    fill_n(match_to, 200, -1);
    int res = 0;
    TIMES(i, N) {
        fill_n(visited, 200, false);
        if(augment(i)) ++res;
    }
    return res;
}

bool solve(int CASE) {
    int G, B, M;
    scanf("%d %d %d", &G, &B, &M);
    if(!G && !B && !M) return false;
    static bool has_edge[200][200];
    TIMES(i, G) {
        graph[i].clear();
        fill_n(has_edge[i], 200, false);
    }
    TIMES(_, M) {
        int x, y;
        scanf("%d %d", &x, &y);
        has_edge[x-1][y-1] = true;
    }
    TIMES(x, G) {
        TIMES(y, B) {
            if(!has_edge[x][y]) {
                graph[x].push_back(y);
            }
        }
    }
    const int res = G+B - bm(G);
    printf("Case %d: %d\n", CASE, res);
    return true;
}

int main() {
    int CASE = 0;
    while(solve(++CASE)) ;
    return 0;
}
