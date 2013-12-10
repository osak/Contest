//Name: Coins
//Level: 4
//Category: 動的計画法,DP
//Note:

/**
 * 個数制限付きナップサック問題。
 * 個数制限なしの場合と同様に実現可能かどうかの表を前から埋めていくが、
 * このとき置ける残りの個数を一緒に管理する。
 * （直前のコインまでで実現可能なところにはcs[i]を起き、そこからas[i]ステップごとに1ずつカウントを減らしていく。
 *
 * オーダーはO(NM)。
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

int dp[100001];
int as[100], cs[100];

bool solve() {
    int N, M;
    scanf("%d %d", &N, &M);
    if(!N && !M) return false;
    fill_n(dp, M+1, -1);
    dp[0] = 0;
    TIMES(i, N) {
        scanf("%d", as+i);
    }
    TIMES(i, N) {
        scanf("%d", cs+i);
    }
    TIMES(i, N) {
        TIMES(j, M+1) {
            if(dp[j] != -1) dp[j] = 0;
        }
        TIMES(j, M+1) {
            if(dp[j] == 0) {
                dp[j] = cs[i];
            } else if(j-as[i] >= 0 && dp[j-as[i]] > 0) {
                dp[j] = dp[j-as[i]] - 1;
            }
        }
    }
    int ans = 0;
    TIMES(i, M) {
        if(dp[i+1] != -1) ++ans;
    }
    printf("%d\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
