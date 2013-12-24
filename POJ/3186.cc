//Name: Treats for the Cows
//Level: 1
//Category: 動的計画法,DP
//Note:

/**
 * 箱の両端をどこまで使ったかでDP。
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

bool solve() {
    int N;
    if(scanf("%d", &N) == EOF) return false;

    static int treats[2001];
    treats[0] = 0;
    TIMES(i, N) {
        scanf("%d", treats+i+1);
    }
    static int dp[2000][2000];
    TIMES(i, N) {
        TIMES(j, N) {
            dp[i][j] = 0;
        }
    }
    int ans = 0;
    for(int i = 1; i <= N; ++i) {
        for(int j = N; j >= i-1; --j) {
            const int d = (i-1) + (N-j);
            dp[i][j] = dp[i-1][j] + treats[i-1]*d;
            if(j+1 <= N) dp[i][j] = max(dp[i][j], dp[i][j+1] + treats[j+1]*d);
            //printf("%d %d %d\n", i, j, dp[i][j]);
            ans = max(ans, dp[i][j]);
        }
    }
    printf("%d\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
