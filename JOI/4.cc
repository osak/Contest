#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ULL;

int main() {
    int N;
    cin >> N;
    vector<int> v(N);
    for(int i = 0; i < N; ++i) cin >> v[i];

    vector<vector<ULL> > dp(N+1, vector<ULL>(21, 0));
    dp[0][v[0]] = 1;

    for(int i = 1; i < N-1; ++i) {
        for(int j = 0; j <= 20; ++j) {
            if(j-v[i] >= 0) dp[i][j] += dp[i-1][j-v[i]];
            if(j+v[i] <= 20) dp[i][j] += dp[i-1][j+v[i]];
            //cout << dp[i][j] << " ";
        }
        //cout << endl;
    }
    cout << dp[N-2][v.back()] << endl;

    return 0;
}
