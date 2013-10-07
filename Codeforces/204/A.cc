//Name: Jeff and Rounding
//Level: 2
//Category: 動的計画法,DP
//Note: Codeforces Round #204(Div.1)

/*
 * dp[i][k] = i番目までの数で、floorをk回使った時の最適解
 * についてDP。
 *
 * オーダーはO(N^2)。
 */
#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <string>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    vector<double> dp(N+1, 1e10);
    dp[0] = 0;
    for(int i = 0; i < 2*N; ++i) {
        double val;
        cin >> val;
        const double a = val - floor(val);
        const double b = val - ceil(val);
        vector<double> next(N+1, 1e10);
        for(int j = 0; j <= min(i+1, N); ++j) {
            next[j] = dp[j] + b;
            if(j-1 >= 0) {
                double d = dp[j-1] + a;
                if(abs(d) < abs(next[j])) {
                    next[j] = d;
                }
            }
        }
        dp.swap(next);
    }
    printf("%.3f\n", abs(dp[N]));
    return 0;
}
