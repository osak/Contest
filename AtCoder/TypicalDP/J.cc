//Name: ボール
//Level: 4
//Category: DP,動的計画法,期待値
//Note: Typical DP Contest J

/*
 * 残っている物のビットパターンをpとして、これを全て倒すまでの期待値をdp[p]とすると
 *   dp[p] = max 1/3(dp[p&(1<<(i-1))] + dp[p&(1<<i)] + dp[p&(1<<(i+1))])
 *   ただし，iはボールを投げる場所
 * と表せる。
 * この式では右辺にdp[p]が出現し得るので、そのような項は左辺に移項して計算する。
 *
 * オーダーはO(2^N*N)。
 */
#include <iostream>
#include <cstdio>

using namespace std;

double memo[1<<16];
bool visited[1<<16];

double calc(int pat) {
    if(pat == 0) return 0;
    double &res = memo[pat];
    if(visited[pat]) return res;
    res = 1e10;
    for(int i = 1; i < 15; ++i) {
        int same = 0;
        double tmp = 0;
        for(int delta = -1; delta <= 1; ++delta) {
            const int np = pat & ~(1<<(i+delta));
            if(np == pat) {
                ++same;
            } else {
                tmp += calc(np) / 3;
            }
        }
        if(same == 3) continue;
        res = min(res, (1+tmp)*3/(3-same));
    }
    //cout << pat << ' ' << res << endl;
    visited[pat] = true;
    return res;
}


int main() {
    cin.tie(0);
    int N;
    cin >> N;
    int pat = 0;
    for(int i = 0; i < N; ++i) {
        int x;
        cin >> x;
        pat |= 1<<x;
    }
    printf("%.7f\n", calc(pat));
    return 0;
}
