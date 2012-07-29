/*
 */
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

int dp[3001][3001];

int main() {
    ios::sync_with_stdio(0);

    int N, T, S;
    cin >> N >> T >> S;

    vector<pair<int,int> > xs(N);
    for(int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        xs[i] = make_pair(x, y);
    }

    for(int i = 0; i < 3001; ++i)
        for(int j = 0; j < 3001; ++j)
            dp[i][j] = 0;

    int ans = 0;
    dp[0][0] = 0;
    for(int t = 0; t <= T; ++t) {
        dp[t][0] = (t>=xs[0].second) ? xs[0].first : 0;
        ans = max(ans, dp[t][0]);
    }

    for(int t = 0; t <= T; ++t) {
        for(int i = 1; i <= N; ++i) {
            if(t > 0) dp[t][i] = dp[t-1][i]; 
            if(i > 0) {
                dp[t][i] = max(dp[t][i], dp[t][i-1]);
                if(t >= xs[i].second) {
                    int prevt = t - xs[i].second;
                    if(!(prevt < S && t > S)) {
                        dp[t][i] = max(dp[t][i], dp[prevt][i-1] + xs[i].first);
                    }
                }
            }
            //cout << t << ' ' << i << ' ' << dp[t][i] << endl;
            ans = max(ans, dp[t][i]);
        }
    }

    cout << ans << endl;
    return 0;
}
