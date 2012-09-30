//Name: Baby Tree
//Level: 2
//Category: 動的計画法,DP
//Note:

/*
 * 状態となるのは直前にどの肥料を与えたかだけである．
 * したがって，i回目の成長率を求めるためには，それぞれに肥料についてi-1回目にその肥料を与えるようなシーケンスでの
 * 最大成長率dp[i-1][j]を記憶しておき，
 *   dp[i][k] = max(j) dp[i-1][j] * g_jk
 * とすればよい．
 *
 * オーダーは状態数N，試行回数M，それぞれの試行で各状態と次状態の組み合わせを試すからN，で O(N^2*M)．
 */
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

double mat[100][100];
double dp[2][100]; //[phase][prev]

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                cin >> mat[i][j];
            }
        }
        for(int i = 0; i < N; ++i) {
            dp[0][i] = 1.0;
        }
        for(int i = 1; i < M; ++i) {
            const int cur = i & 1;
            const int prev = cur ^ 1;
            for(int j = 0; j < N; ++j) {
                dp[cur][j] = 0.0;
                for(int last = 0; last < N; ++last) {
                    dp[cur][j] = max(dp[cur][j], dp[prev][last] * mat[last][j]);
                }
            }
        }
        double ans = 0.0;
        for(int i = 0; i < N; ++i) {
            ans = max(ans, dp[(M-1)&1][i]);
        }
        printf("%.2f\n", ans);
    }
    return 0;
}
