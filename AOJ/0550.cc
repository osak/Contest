//Name: Dividing Snacks
//Level: 3
//Category: DP,動的計画法
//Note:

/*
 * ブロックを左から順にA,Bに割り振っていき，AをN/2個取ることを考える．
 * i番目のブロックをAにするとき，
 * ・i-1番目がAなら追加コスト0(ただし，これがちょうどN/2個目のときは直後で切断しないといけない)
 * ・i-1番目がBなら追加コストcost[i-1]
 * i番目のブロックをBにするとき，
 * ・i-1番目がAなら追加コストcost[i-1]
 * ・i-1番目がBなら追加コスト0
 * で割り振ることができる．
 * よって状態は，
 * ・直前のブロックをAとBどちらにしたか
 * ・あといくつAを取れば良いか
 * で定められるから，各状態について最小コストを覚えながらDPする．
 *
 * オーダーは O(N^2)。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

inline bool update(int &a, int v) {
    if(a < v) return false;
    a = v;
    return true;
}
// dp[ptr][which][need]
// which: A=0, B=1
// need: remaining of A
int dp[2][2][5001];
const int INF = 10000*10000;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    vector<int> cost(N-1);
    for(int i = 0; i < N-1; ++i) {
        cin >> cost[i];
    }
    int ans = INF;
    int ptr = 0;
    fill_n(dp[ptr][0], N/2+1, INF);
    fill_n(dp[ptr][1], N/2+1, INF);
    dp[ptr][0][N/2-1] = 0;
    dp[ptr][1][N/2] = 0;
    ptr ^= 1;
    for(int i = 1; i < N; ++i) {
        int prev = ptr ^ 1;
        fill_n(dp[ptr][0], N/2+1, INF);
        fill_n(dp[ptr][1], N/2+1, INF);
        for(int j = 0; j <= N/2; ++j) {
            // 直前がAのとき
            if(j+1 <= N/2) update(dp[ptr][0][j], dp[prev][0][j+1]);
            update(dp[ptr][1][j], dp[prev][0][j] + cost[i-1]);
            
            // 直前がBのとき
            if(j+1 <= N/2) update(dp[ptr][0][j], dp[prev][1][j+1] + cost[i-1]);
            update(dp[ptr][1][j], dp[prev][1][j]);

            // ここで残りが0になるなら，直後で切らないといけない
            if(j == 0) {
                if(i < N-1) dp[ptr][0][j] += cost[i];
            }
            //cout << j << ": " << dp[ptr][0][j] << ' ' << dp[ptr][1][j] << endl;
        }
        update(ans, min(dp[ptr][0][0], dp[ptr][1][0]));
        ptr ^= 1;
    }
    cout << ans << endl;
    return 0;
}
