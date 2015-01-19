//Name: Restore Calculation
//Level: 3
//Category: 動的計画法,DP
//Note: 

/**
 * dp[i][j] = i桁目以降のパターン数(i桁目はi-1桁目にj繰り上げる)
 * とすると、
 *   dp[i][0] = (和が9以下になる組み合わせ) × dp[i+1][0] + (和が8以下になる組み合わせ) × dp[i+1][1]
 *   dp[i][1] = (和が10以上になる組み合わせ) × dp[i+1][0] + (和が9以上になる組み合わせ) × dp[i+1][1]
 * で計算できる。
 * 既存の文字と整合性が取れるものだけを採用するように注意。
 *
 * オーダーは O(|S| D^2)。
 * ただしDは数字の種類数で、D = 10。
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const long long MOD = 1000000007;
bool solve(bool first) {
    string s1, s2, sum;
    if(!(cin >> s1 >> s2 >> sum)) return false;
    if(s1 == "0") return false;

    const int S = s1.size();
    vector<vector<long long>> dp(S+1, vector<long long>(2, 0));
    dp[S][0] = 1;
    for(int i = S-1; i >= 0; --i) {
        for(int a = (i==0); a <= 9; ++a) {
            if(s1[i] != '?' && s1[i] != a+'0') continue;
            for(int b = (i==0); b <= 9; ++b) {
                if(s2[i] != '?' && s2[i] != b+'0') continue;
                const int s = (a + b) % 10;

                if(a+b <= 9) {
                    if(sum[i] == '?' || sum[i] == s+'0') {
                        dp[i][0] += dp[i+1][0];
                    }
                }
                if(a+b <= 8) {
                    if(sum[i] == '?' || sum[i] == s+1+'0') {
                        dp[i][0] += dp[i+1][1];
                    }
                }
                if(a+b >= 10) {
                    if(sum[i] == '?' || sum[i] == s+'0') {
                        dp[i][1] += dp[i+1][0];
                    }
                }
                if(a+b >= 9) {
                    if(sum[i] == '?' || sum[i] == (s+1)%10+'0') {
                        dp[i][1] += dp[i+1][1];
                    }
                }
                dp[i][0] %= MOD;
                dp[i][1] %= MOD;
            }
        }
    }
    cout << dp[0][0] << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
