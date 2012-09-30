//Name: A New Plan of Aizu Ski Resort
//Level: 2
//Category: 動的計画法,DP
//Note:

/*
 * 地図の上から順に見ていき，配るDPで更新していけばよい．
 * ジャンプ台でマップの外に出てゴールする場合があるので，Y方向に1行余分に取っておくとよい．
 *
 * オーダーは各マスを見るだけなので O(XY)．
 */
#include <iostream>
#include <vector>

using namespace std;

int dp[32][15]; // dp[Y][X]
int field[32][16];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int X, Y;
        cin >> X >> Y;
        if(!X && !Y) break;

        // Initialize
        for(int i = 0; i < Y; ++i) {
            for(int j = 0; j < X; ++j) {
                cin >> field[i][j];
                dp[i][j] = 0;
            }
        }
        for(int j = 0; j < X; ++j) {
            dp[Y][j] = 0;
        }

        // Base case
        for(int i = 0; i < X; ++i) {
            if(field[0][i] == 0) dp[0][i] = 1;
            else dp[0][i] = 0;
        }
        for(int i = 0; i < Y-1; ++i) {
            for(int j = 0; j < X; ++j) {
                if(field[i][j] == 0) {
                    // Move
                    for(int dx = -1; dx <= 1; ++dx) {
                        const int nx = j + dx;
                        if(nx < 0 || nx >= X) continue;
                        if(field[i+1][nx] == 0) dp[i+1][nx] += dp[i][j];
                        else if(dx == 0 && field[i+1][nx] == 2) dp[i+1][nx] += dp[i][j];
                    }
                } else if(field[i][j] == 2) {
                    // Jump
                    if(field[i+2][j] != 1) dp[i+2][j] += dp[i][j];
                }
            }
        }
        int ans = 0;
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < X; ++j) {
                ans += dp[Y-1+i][j];
            }
        }
        cout << ans << endl;
    }
    return 0;
}
