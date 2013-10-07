//Name: 準急
//Level: 4
//Category: DP,動的計画法
//Note: Typical DP Contest F

/*
 * 駅(i-1)を通過駅としたとき、駅i以降のパターンをdp[i]とすると
 * ・駅iを通過するパターン： dp[i+1]通り
 * ・駅iからk < K駅連続で停車し、その後通過するパターン： ∑dp[i+k-1+2] 通り
 * これをそのまま実装するとO(N^2)になってしまうが、dp表を後ろから埋めていき、
 * 2番目のパターンを累積和で計算できるようにすると O(N) に落とすことができる。
 */
#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

const LL MOD = 1000000007LL;
LL memo[1000001];
bool visited[1000001];
int N, K;

// 再帰実装(TLE)
LL calc(int pos) {
    if(pos >= N) {
        // N-1に止まる制約(N-1に止まる→次はN+1から開始)
        if(pos == N+1) return 1;
        else return 0;
    }
    LL &res = memo[pos];
    if(visited[pos]) {
        return res;
    }
    // 0に止まる制約
    // 0以外ではposを通過にしてもよい。
    res = pos == 0 ? 0 : calc(pos+1);
    for(int i = pos; i < N && i < pos+K-1; ++i) {
        res += calc(i+2);
        res %= MOD;
    }
    visited[pos] = true;
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> K;
    vector<LL> dp(1000003, 0);
    vector<LL> sum(1000003, 0);
    dp[N+1] = 1;
    sum[N+1] = sum[N] = 1;
    for(int i = N-1; i >= 0; --i) {
        dp[i] = i == 0 ? 0 : dp[i+1];
        const int ntop = min(i+2, N+2);
        const int ntail = min(i+K+1, N+2);
        dp[i] += (sum[ntop] - sum[ntail] + MOD) % MOD;
        dp[i] %= MOD;
        sum[i] = sum[i+1] + dp[i];
        sum[i] %= MOD;
        //cout << i << ": " << dp[i] << ' ' << calc(i) << endl;
    }
    cout << dp[0] << endl;

    return 0;
}
