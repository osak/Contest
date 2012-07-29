#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Tag {
    int a, b;

    bool operator < (const Tag &other) const {
        return b < other.b;
    }
};

int main() {
    int N;
    cin >> N;
    vector<Tag> probs(N);
    for(int i = 0; i < N; ++i)
        cin >> probs[i].a >> probs[i].b;

    sort(probs.begin(), probs.end());

    //[probs][solved] = time
    vector<vector<int> > dp(N+1, vector<int>(N+1, INT_MAX/2));
    for(int i = 0; i < N+1; ++i) 
        dp[i][0] = 0;
    int ans = 0;
    for(int i = 1; i <= probs.size(); ++i) {
        for(int j = 1; j <= probs.size(); ++j) {
            dp[i][j] = dp[i-1][j];
            if(dp[i-1][j-1] + probs[i-1].a <= probs[i-1].b) {
                dp[i][j] = min(dp[i][j], dp[i-1][j-1]+probs[i-1].a);
                ans = max(ans, j);
            }
        }
    }

    cout << ans << endl;
    
    return 0;
}
