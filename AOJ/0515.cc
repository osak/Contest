//Name: School Road
//Level: 2
//Category: 動的計画法,DP
//Note:

#include <iostream>
#include <vector>

using namespace std;

int main() {
    while(true) {
        int a, b;
        cin >> a >> b;
        if(!a && !b) break;

        vector<vector<int> > dp(a, vector<int>(b, 0));
        dp[0][0] = 1;

        int n;
        cin >> n;
        while(n--) {
            int x, y;
            cin >> x >> y;
            --x; --y;
            dp[x][y] = -1;
        }
        for(int i = 0; i < a; ++i) {
            for(int j = 0; j < b; ++j) {
                if(dp[i][j] == -1) continue;
                if(i-1 >= 0 && dp[i-1][j] != -1) dp[i][j] += dp[i-1][j];
                if(j-1 >= 0 && dp[i][j-1] != -1) dp[i][j] += dp[i][j-1];
                if(i+1 < a && dp[i+1][j] != -1) dp[i][j] += dp[i+1][j];
                if(j+1 < b && dp[i][j+1] != -1) dp[i][j] += dp[i][j+1];
            }
        }

        cout << dp[a-1][b-1] << endl;
    }
    return 0;
}
