#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ULL;

int main() {
    vector<ULL> dp(31, 1);

    dp[0] = dp[1] = dp[2] = 1;
    int sum = 2;
    for(int i = 3; i < 30; ++i) {
        for(int j = 1; j <= i; ++j) {
            int rem = min(j-1, i-j);
            ULL cnt = 0;
            for(int k = 0; k <= rem; ++k) {
                for(int l = 0; l <= min(rem, i-k-1); ++l) {
                    cnt += 1;
                }
            }
            dp[i] *= cnt;
        }
        cout << dp[i] << " ";
        dp[i] /= 2;
        if(dp[i] >= 4) dp[i] /= 2;
        cout << dp[i] << endl;
    }

    int N;
    while(cin >> N && !cin.eof()) {
        cout << dp[N] << endl;
    }
    return 0;
}
