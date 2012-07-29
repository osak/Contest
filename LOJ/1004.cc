#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    for(int CASE = 1; CASE <= T; ++CASE) {
        int N;
        cin >> N;

        int size = 2*N-1;
        vector<vector<int> > v(size, vector<int>(size, 0));
        for(int i = 0; i < size; ++i) {
            int cols = (i<N)?(i+1):(size-i);
            for(int j = 0; j < cols; ++j) {
                cin >> v[i][j];
            }
        }

        vector<vector<int> > dp(size, vector<int>(size, 0));
        dp[0][0] = v[0][0];
        for(int i = 1; i < size; ++i) {
            int cols = (i<N)?(i+1):(size-i);
            for(int j = 0; j < cols; ++j) {
                if(i < N) {
                    if(j > 0) dp[i][j] = max(dp[i][j], dp[i-1][j-1]+v[i][j]);
                    dp[i][j] = max(dp[i][j], dp[i-1][j]+v[i][j]);
                }
                else {
                    if(j+1 < size) dp[i][j] = max(dp[i][j], dp[i-1][j+1]+v[i][j]);
                    dp[i][j] = max(dp[i][j], dp[i-1][j]+v[i][j]);
                }
            }
        }
        cout << "Case " << CASE << ": " << dp[size-1][0] << endl;
    }

    return 0;
}
