//Name: Pasta
//Level: 2
//Category: 動的計画法,DP
//Note:

/*
 * 状態となるのは
 * ・今何日目か
 * ・最後にどのソースを使ったか
 * ・最後のソースは2日連続か
 * の3つ．
 * N日目にソースiを使ったときのパターン数は
 * ・N-1日目にソースj(j≠i)を使うときの合計パターン数(このとき，最後に使ったソースiは1日目)
 * ・N-1日目にソースiを使い，かつそれが1日目であるときのパターン数(このとき，最後に使ったソースiは2日連続)
 * で表わせる．
 * あらかじめ使うソースが決まっている日では，そのソース以外の数値が0になるよう処理すればよい．
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 10000;

// dp[day][last][second]
int dp[100][3][2];
int plan[100];

int main() {
    int N, K;
    cin >> N >> K;
    fill_n(plan, N, -1);
    for(int i = 0; i < K; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        plan[a] = b;
    }

    if(plan[0] == -1) {
        dp[0][0][0] = dp[0][1][0] = dp[0][2][0] = 1;
    }
    else {
        dp[0][plan[0]][0] = 1;
    }
    for(int day = 1; day < N; ++day) {
        if(plan[day] == -1) {
            for(int sauce = 0; sauce < 3; ++sauce) {
                for(int prev = 0; prev < 3; ++prev) {
                    if(prev != sauce) {
                        dp[day][sauce][0] += dp[day-1][prev][0] + dp[day-1][prev][1];
                    }
                    else {
                        dp[day][sauce][1] += dp[day-1][prev][0];
                    }
                }
            }
        }
        else {
            int sauce = plan[day];
            for(int prev = 0; prev < 3; ++prev) {
                if(prev != sauce) dp[day][sauce][0] += dp[day-1][prev][0] + dp[day-1][prev][1];
                else dp[day][sauce][1] += dp[day-1][prev][0];
            }
        }
        for(int sauce = 0; sauce < 3; ++sauce) {
            dp[day][sauce][0] %= MOD;
            dp[day][sauce][1] %= MOD;
        }
    }
    int sum = 0;
    for(int sauce = 0; sauce < 3; ++sauce) {
        sum += dp[N-1][sauce][0] + dp[N-1][sauce][1];
    }
    cout << sum%MOD << endl;
    return 0;
}
