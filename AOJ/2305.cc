#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX = 200001;
double dp[20][MAX];

int main() {
    int N;
    cin >> N;

    vector<int> a(N);
    for(int i = 0; i < N; ++i) cin >> a[i];

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < MAX; ++j) dp[i][j] = -1;
    }

    for(int i = 0; i < N; ++i) {
        for(int j = 1; j < MAX; ++j) {
            dp[i][j] = max(dp[i][j], fabs(a[i]-j) / (double)a[i]);
            //cout << i << ' ' << j << ' ' << dp[i][j] << endl;

            if(i+1 < N) {
                for(int k = j; k < MAX; k += j) {
                    if(dp[i+1][k] < 0 || dp[i+1][k] > dp[i][j]) {
                        dp[i+1][k] = dp[i][j];
                    }
                }
                for(int k = j; k >= 0; k -= j) {
                    if(dp[i+1][k] < 0 || dp[i+1][k] > dp[i][j]) {
                        dp[i+1][k] = dp[i][j];
                    }
                }
            }
        }
    }

    double ans = 1e10;
    for(int i = 1; i < MAX; ++i) {
        ans = min(ans, dp[N-1][i]);
    }

    printf("%.8f\n", ans);

    return 0;
}
