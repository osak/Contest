//Name: Rebuilding Roads
//Level: 3
//Category: 木,Tree,Tree DP
//Note:

/**
 * dp[i][n] = ノードiとその子でnノードのサブツリーを作るときのコスト
 * とすると、子jをひとつづつ追加していきながら
 * ・iとjの間を切断するとき、dp[i][n] = dp[i][n]+1
 * ・iとjをつないでおくとき、dp[i][n] = min(dp[i][n-k] + dp[j][k])
 * とすることで計算できる。
 * 最後に、各ノードを根としたときにPノードのサブツリーを作るコストを計算する。
 *
 * オーダーはO(N^2)。
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

const int INF = 10000;
vector<int> graph[150];
int root_of[150];
int dp[150][151];
bool visited[150];
int N;

void to_rooted(int pos, int root) {
    root_of[pos] = root;
    const int M = graph[pos].size();
    for(int i = 0; i < M; ++i) {
        if(graph[pos][i] == root) continue;
        to_rooted(graph[pos][i], pos);
    }
}

void calc(int pos) {
    if(visited[pos]) return;
    for(int i = 0; i <= N; ++i) {
        dp[pos][i] = INF;
    }
    dp[pos][1] = 0;
    const int M = graph[pos].size();
    for(int i = 0; i < M; ++i) {
        const int child = graph[pos][i];
        if(child == root_of[pos]) continue;
        calc(child);
        for(int j = N; j >= 1; --j) {
            // Case 1. not connect with this child
            dp[pos][j]++;
            // Case 2. connect with this child
            for(int k = 1; k < j; ++k) {
                dp[pos][j] = min(dp[pos][j], dp[pos][j-k] + dp[child][k]);
            }
        }
    }
}

bool solve() {
    int P;
    if(scanf("%d %d", &N, &P) == EOF) return false;
    for(int i = 0; i < N; ++i) {
        graph[i].clear();
    }
    for(int i = 0; i < N-1; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        --a; --b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    fill_n(visited, N, false);
    to_rooted(0, -1);
    calc(0);
    int ans = INF;
    for(int i = 0; i < N; ++i) {
        int cost = dp[i][P];
        if(i != 0) ++cost;
        ans = min(ans, cost);
    }
    printf("%d\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
