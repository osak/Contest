#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const unsigned MOD = 1000000007;
unsigned dp[1001][1001];

int main() {
    dp[1][1] = 1;
    for(int i = 2; i <= 1000; ++i) {
        for(int r = 1; r <= i; ++r) {
            unsigned long long tmp = (unsigned long long)dp[i-1][r]*r + dp[i-1][r-1];
            dp[i][r] = (unsigned)(tmp % MOD);
        }
    }

    int T;
    scanf("%d", &T);
    while(T--) {
        int N;
        scanf("%d", &N);
        unsigned ans = 0;
        for(int i = 1; i <= N; ++i) {
            ans += dp[N][i];
            ans %= MOD;
        }
        printf("%d\n", ans);
    }

    return 0;
}
