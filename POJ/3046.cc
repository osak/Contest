//Name: Ant Counting
//Level: 3
//Category: 動的計画法,DP
//Note:

/**
 * 種類ごとの蟻の数を個数、価値を全て1とした個数制限つきナップサック問題で、ある価値を達成できる入れ方の総数を求める問題。
 * 直前の荷物までで達成できる価値jについて、そこからcnt[i]まで大きい価値はユニークに達成できるため、この区間にdp[j]を加えたい。
 * これは累積和（いもす法）を使うことで高速に処理できる。
 *
 * オーダーはO(TA)。
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

const int MOD = 1000000;
const int MAX = 1000*100+1;

int dp[MAX];
int acc[MAX];
int reachdp[MAX];
int cnt[1000];

bool solve() {
    int T, A, S, B;
    scanf("%d %d %d %d", &T, &A, &S, &B);
    TIMES(_, A) {
        int v;
        scanf("%d", &v);
        cnt[v-1]++;
    }
    fill_n(dp, A+1, -1);
    dp[0] = 1;
    TIMES(i, T) {
        fill_n(acc, A+1, 0);
        fill_n(reachdp, A+1, 0);
        TIMES(j, A) {
            if(dp[j] != -1) {
                acc[j+1] += dp[j];
                acc[j+1] %= MOD;
                reachdp[j]++;
                if(j+cnt[i]+1 < A+1) {
                    acc[j+cnt[i]+1] -= dp[j];
                    acc[j+cnt[i]+1] += MOD;
                    acc[j+cnt[i]+1] %= MOD;
                    reachdp[j+cnt[i]+1]--;
                }
            }
        }
        TIMES(j, A) {
            acc[j+1] += acc[j];
            acc[j+1] %= MOD;
            reachdp[j+1] += reachdp[j];
            //if(reachdp[j] > 0) printf("%d %d\n", j, reachdp[j]);
        }
        TIMES(j, A+1) {
            if(dp[j] == -1) {
                if(reachdp[j] > 0) dp[j] = acc[j];
            } else {
                dp[j] += acc[j];
                dp[j] %= MOD;
            }
        }
    }
    int ans = 0;
    for(int i = S; i <= B; ++i) {
        if(dp[i] != -1) {
            ans += dp[i];
            ans %= MOD;
        }
    }
    printf("%d\n", ans);
    return false;
}

int main() {
    while(solve()) ;
    return 0;
}
