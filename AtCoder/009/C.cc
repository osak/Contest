/*
 * 順列のうち，元と同じ場所にある要素の存在しないものを完全順列，と言うらしい．
 * とりあえず K 要素の完全順列を考えてから nCk を掛ければよい．
 *
 * K 要素の完全順列は，
 * ・K-1 要素の完全順列の末尾に1要素加え(この時点では末尾の要素が完全性を破壊する)，
 *   末尾の要素を任意の要素と入れ替える．
 * ・K-1 要素で1要素だけ元と同じ場所にあるような順列の末尾に1要素加え，
 *   これらの要素を入れ替える
 * という操作で構築できる．
 * あとは DP でパターンを求める．
 * オーバーフローに注意．
 *
 * オーダーは O(K)．
 */
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ULL;

const ULL MOD = 1777777777;

ULL modpow(ULL a, ULL x) {
    if(x == 0) return 1;
    if(x == 1) return a;
    ULL half = modpow(a, x/2);
    ULL rem = (x&1) ? a : 1;
    return (half*half) % MOD * rem % MOD;
}

ULL comb(ULL n, ULL k) {
    ULL res = 1;
    for(ULL i = n-k+1; i <= n; ++i) {
        res *= i;
        res %= MOD;
    }
    for(ULL i = 1; i <= k; ++i) {
        res *= modpow(i, MOD-2);
        res %= MOD;
    }
    return res;
}

ULL dp[2][2];
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    ULL N, K;
    cin >> N >> K;
    dp[0][0] = 0;
    dp[0][1] = 1;
    for(int i = 2; i <= (int)K; ++i) {
        const int prev = i&1;
        const int cur = prev^1;
        dp[cur][0] = ((dp[prev][0]*(i-1)) % MOD + dp[prev][1]) % MOD;
        dp[cur][1] = dp[prev][0]*i % MOD;
    }
    cout << (dp[(K+1)&1][0] * comb(N % MOD, K)) % MOD << endl;
    return 0;
}
