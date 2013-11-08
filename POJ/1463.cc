//Name: Strategic game
//Level: 2
//Category: 二部グラフ,最小点被覆,Minimum Vertex Cover
//Note:

/**
 * 全体が木になっているので、このグラフは二部グラフである。
 * したがって、最小点被覆は二部グラフの最大マッチングと等しい。
 * (König's Theorem)
 *
 * オーダーはO(NM)。
 * ただしMは辺の総数。
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

vector<int> graph[1500];
int match_to[1500];
bool visited[1500];

bool match(int pos) {
    if(pos == -1) return true;
    if(visited[pos]) return false;

    const int M = graph[pos].size();
    visited[pos] = true;
    for(int i = 0; i < M; ++i) {
        const int next = graph[pos][i];
        if(match(match_to[next])) {
            match_to[next] = pos;
            return true;
        }
    }
    return false;
}

int bm(int N) {
    int res = 0;
    fill_n(match_to, N, -1);
    for(int i = 0; i < N; ++i) {
        fill_n(visited, N, false);
        if(match(i)) ++res;
    }
    return res;
}

bool solve() {
    int N;
    if(scanf("%d", &N) == EOF) return false;
    for(int i = 0; i < N; ++i) {
        graph[i].clear();
    }
    for(int i = 0; i < N; ++i) {
        int id, M;
        scanf("%d : ( %d )", &id, &M);
        while(M--) {
            int to;
            scanf(" %d", &to);
            graph[id].push_back(to);
            graph[to].push_back(id);
        }
    }
    printf("%d\n", bm(N)/2);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
