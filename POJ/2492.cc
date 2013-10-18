//Name: A Bug's Life
//Level: 1
//Category: 探索,グラフ,Graph,二部グラフ,彩色問題
//Note:

/**
 * グラフ全体が二部グラフであるか、すなわち二彩色可能かどうかを判定すればよい。
 * 各頂点から深さ優先探索しながら色を塗っていくことで、この判定は可能。
 *
 * オーダーはO(N+E)。
 * ただしNは頂点数、Eは辺数。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

bool dfs(int pos, int c, vector<int> &color, const vector<vector<int> > &graph) {
    if(color[pos] != -1) {
        return color[pos] == c;
    }
    color[pos] = c;
    const vector<int> &v = graph[pos];
    for(vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        if(!dfs(*it, 1-c, color, graph)) return false;
    }
    return true;
}

bool solve(int CASE) {
    int N, E;
    if(scanf("%d %d", &N, &E) == EOF) return false;
    vector<vector<int> > graph(N);
    while(E--) {
        int a, b;
        scanf("%d %d", &a, &b);
        --a; --b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vector<int> color(N, -1);
    bool ok = true;
    TIMES(i, N) {
        if(color[i] != -1) continue;
        if(!dfs(i, 0, color, graph)) {
            ok = false;
            break;
        }
    }
    printf("Scenario #%d:\n", CASE);
    if(ok) {
        puts("No suspicious bugs found!");
    } else {
        puts("Suspicious bugs found!");
    }
    puts("");
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    scanf("%d", &N);
    for(int CASE = 1; CASE <= N; ++CASE) {
        solve(CASE);
    }
    return 0;
}

