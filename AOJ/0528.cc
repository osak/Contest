#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string s1, s2;
    while(cin >> s1 >> s2) {
        //vector<vector<int> > dp(s1.size(), vector<int>(s2.size(), 0));
        vector<int> dp[2];
        dp[0].resize(s2.size());
        dp[1].resize(s2.size());
        fill(dp[0].begin(), dp[0].end(), 0);
        fill(dp[1].begin(), dp[1].end(), 0);

        int ans = 0;
        int l1 = s1.size();
        int l2 = s2.size();
        for(int i = 0; i < l1; ++i) {
            int curr = i&1;
            int prev = 1-curr;
            for(int j = 0; j < l2; ++j) {
                if(s1[i] == s2[j]) {
                    if(i > 0 && j > 0) dp[curr][j] = dp[prev][j-1]+1;
                    else dp[curr][j] = 1;
                }
                else dp[curr][j] = 0;
                if(dp[curr][j] > ans) ans = dp[curr][j];
            }
        }
        cout << ans << endl;
    }
    return 0;
}
