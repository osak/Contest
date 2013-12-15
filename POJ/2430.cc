//Name: Lazy Cows
//Level: 3
//Category: 動的計画法,DP
//Note:

/**
 * 牛がいるx座標だけを考えた時、納屋の置き方は
 *   o o . ^
 *   o . o v
 * の4通り（最後のものは縦長の納屋）。
 * 納屋の消費個数は、これらが前のパターンと繋がるかどうかで決まる。
 * 繋がるかどうかの判定は直前の列のパターンさえ覚えておけばよいので、
 * [x位置][置いた納屋][直前のパターン]でDP。
 *
 * オーダーはO(N^2)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

bool solve() {
    int N, K, B;
    if(scanf("%d %d %d", &N, &K, &B) == EOF) return false;
    if(!N && !K && !B) return false;
    map<int,int> cows;
    TIMES(_, N) {
        int r, c;
        scanf("%d %d", &r, &c);
        cows[c] += r;
    }
    static int dp[1002][1002][4];
    TIMES(i, N+2) {
        TIMES(j, N+2) {
            TIMES(p, 4) {
                dp[i][j][p] = 2*B;
            }
        }
    }
    int prev_x = 0;
    int i = 0;
    TIMES(p, 4) {
        dp[0][0][p] = 0;
    }
    ++i;
    for(map<int,int>::iterator it = cows.begin(); it != cows.end(); ++it) {
        const int x = it->first;
        //printf("%d\n", x);
        const int cow = it->second;
        const int d = x - prev_x;
        for(int b = 1; b <= K; ++b) {
            if(b >= 2) {
                dp[i][b][0] = min(dp[i][b][0], min(dp[i-1][b-1][0], dp[i-1][b-1][1]) + d + 1);
                dp[i][b][0] = min(dp[i][b][0], min(dp[i-1][b-1][1], dp[i-1][b-1][2]) + d + 1);
                dp[i][b][0] = min(dp[i][b][0], dp[i-1][b][0] + d*2);
            }

            dp[i][b][1] = min(dp[i][b][1], min(dp[i-1][b][0], dp[i-1][b][1]) + d);
            
            dp[i][b][2] = min(dp[i][b][2], min(dp[i-1][b][0], dp[i-1][b][2]) + d);

            dp[i][b][3] = min(dp[i][b][3], dp[i-1][b][3] + d*2);
            for(int pp = 0; pp <= 3; ++pp) {
                if(b >= 2) dp[i][b][0] = min(dp[i][b][0], dp[i-1][b-2][pp] + 2);
                dp[i][b][1] = min(dp[i][b][1], dp[i-1][b-1][pp] + 1);
                dp[i][b][2] = min(dp[i][b][2], dp[i-1][b-1][pp] + 1);
                dp[i][b][3] = min(dp[i][b][3], dp[i-1][b-1][pp] + 2);
            }
            if(cow&1) dp[i][b][1] = 2*B;
            if(cow&2) dp[i][b][2] = 2*B;
            /*
            TIMES(p, 4) {
                printf("%d %d %d %d\n", i, b, p, dp[i][b][p]);
            }
            */
        }
        prev_x = x;
        ++i;
    }
    int ans = 2*B;
    TIMES(p, 4) {
        ans = min(ans, dp[i-1][K][p]);
    }
    printf("%d\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
