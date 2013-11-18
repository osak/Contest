//Name: Beautiful Spacing
//Level: 4
//Category: 動的計画法,DP,二分探索
//Note:

/**
 * 最大値の最小化なので二分探索。
 *
 * 使える空白の長さの上限xを決めたとき、単語iから行を始めて最後まで埋められるかどうかは
 * ・単語iからk語をこの行に入れ、次の行をi+kから始めたときに最後まで埋められるか
 * という問題に帰着できる。
 * ここで、単語iと同じ行に入れられる語数について、
 * ・下限はw[i] + x + w[i+1] + x + ... + w[i+k] >= W となる最小のk+1
 * ・上限はw[i] + 1 + w[i+1] + 1 + ... + w[i+l] > W となる最小のl
 * である。
 * 前者の制約は、w[i+k]を入れないと空白長さの上限制約を満たせないことによる。
 * 後者の制約は、w[i+l]を入れると空白で語を区切れなくなることによる。
 * これらの境界値は、w[i]の累積和を使って二分探索で求めることができる。
 *
 * 以上より、i+k+1からi+l-1までのどれかが、行頭に来た時に埋められるようになっていればよい。
 * これは累積和を管理することでO(1)で求められる。
 *
 * オーダーはO(N log W log N)。
 * この方法だと、AOJではTLEが厳しい。
 */
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define TIMES(i, n) for(int i = 0; i < (n); ++i)

template<class Pred>
int binsearch(const Pred &pred) {
    int val = 0;
    for(int bit = 17; bit >= 0; --bit) {
        const int next = val + (1<<bit);
        val = pred(next) ? next : val;
    }
    return val;
}

bool solve() {
    int W, N;
    scanf("%d %d", &W, &N);
    if(!W && !N) return false;

    vector<long long> sum(N+2, 0);
    TIMES(i, N) {
        int v;
        scanf("%d", &v);
        sum[i+1] = v;
        sum[i+1] += sum[i];
    }
    sum[N+1] = sum[N];

    vector<int> dp(N+3, 0);
    int ans = binsearch([&](long long x) {
        if(x > W) return false;
        fill(dp.begin(), dp.end(), 0);
        dp[N+2] = 0;
        dp[N+1] = 1;
        for(int i = N; i > 0; --i) {
            const int mink = binsearch([&](int k) {
                if(i+k > N) return false;
                const long long len = (sum[i+k] - sum[i-1]) + k*x;
                return len < W;
            }) + 2;
            const int maxk = binsearch([&](int k) {
                if(i+k > N) return false;
                const long long len = (sum[i+k] - sum[i-1]) + k;
                return len <= W;
            }) + 1;
            //cout << x << ' ' << i << ' ' << mink << ' ' << maxk << endl;
            dp[i] = (i+maxk == N+1) || (mink <= maxk && dp[i+mink] - dp[i+maxk+1] > 0);
            //cout << dp[i] << endl;
            dp[i] += dp[i+1];
        }
        return dp[1] - dp[2] == 0;
    }) + 1;
    printf("%d\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
