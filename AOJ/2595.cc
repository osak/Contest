//Name: Cookie Counter
//Level: 3
//Category: 数学,数え上げ,動的計画法,DP
//Note:

/**
 * D日のうちe日だけクッキーを1枚以上食べたとすると、そういう日の取り方は全部でcomb(D, e)通りある。
 * 毎日1枚以上のクッキーを食べるとしたとき、e日目にクッキーがk枚だけ残っているような食べ方のパターン数は
 *   dp[e][k] = Σdp[e-1][k+1 ≦ k' < k+X]
 * であるが、dp[e][N]からdp[e][0]に向けて埋めていくと、Σの中身を再利用できるため、更新がO(1)になる。
 *
 * オーダーは O(N^2)。
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const long long MOD = 1000000007;

long long modpow(long long a, long long x) {
    long long res = 1;
    while(x) {
        if(x & 1) {
            res *= a;
            res %= MOD;
        }
        a *= a;
        a %= MOD;
        x /= 2;
    }
    return res;
}

long long inv(long long x) {
    return modpow(x, MOD-2);
}

long long inv_tbl[2001];

bool solve() {
    int N, X;
    long long D;
    if(!(cin >> N >> D >> X)) return false;
    if(!N && !D && !X) return false;

    long long ans = 0;
    long long comb = 1;
    vector<long long> dp[2];
    dp[0].resize(N+1);
    dp[1].resize(N+1);
    dp[0][N] = 1;
    for(int d = 1; d <= min<long long>(N,D); ++d) {
        long long acc = 0;
        for(int k = N; k >= 0; --k) {
            dp[1][k] = acc;
            acc += dp[0][k];
            if(k+X-1 <= N) acc += (MOD - dp[0][k+X-1]);
            acc %= MOD;
        }
        comb *= (D-d+1) % MOD;
        comb %= MOD;
        comb *= inv_tbl[d];
        comb %= MOD;
        ans += dp[1][0] * comb;
        ans %= MOD;
        dp[0].swap(dp[1]);
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    for(int i = 1; i <= 2000; ++i) {
        inv_tbl[i] = inv(i);
    }

    while(solve()) ;
    return 0;
}
