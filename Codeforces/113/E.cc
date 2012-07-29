#include <iostream>

using namespace std;

int dp[10000001][4];

int main() {
    int N;
    cin >> N;

    dp[0][3] = 1;
    for(int i = 1; i <= N; ++i) {
        int sum = 0;
        for(int j = 0; j < 4; ++j) {
            sum += dp[i-1][j];
            sum %= 1000000007;
        }
        for(int j = 0; j < 4; ++j) {
            dp[i][j] = (sum-dp[i-1][j]+1000000007) % 1000000007;
        }
    }

    cout << dp[N][3] << endl;
    return 0;
}
