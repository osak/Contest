#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

struct Tag { 
    int s, p, c;
};

int main() {
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<Tag> tags(N);
        vector<int> mincost(M, INT_MAX);
        for(int i = 0; i < N; ++i) cin >> tags[i].s >> tags[i].p >> tags[i].c;

        for(int i = 0; i < M; ++i) {
            int S, P;
            cin >> S >> P;
            vector<vector<int> > dp(S+1, vector<int>(P+1, -1));
            dp[0][0] = 0;
            for(int j = 0; j <= P; ++j) {
                for(int k = 0; k <= S; ++k) {
                    if(dp[k][j] == -1) continue;
                    for(int l = 0; l < N; ++l) {
                        int ns = k + tags[l].s;
                        int np = j + tags[l].p;
                        int nc = dp[k][j] + tags[l].c;
                        if(ns > S) continue;
                        else if(np >= P) mincost[i] = min(mincost[i], nc);
                        else dp[ns][np] = nc;
                    }
                }
            }
        }

        int ans = INT_MAX;
        vector<int> v(M, 1);
        for(int i = 0; i < M/2+1; ++i) v[i] = 0;
        do {
            int sum = 0;
            for(int i = 0; i < M; ++i) 
                if(v[i]==0) {
                    if(mincost[i] == INT_MAX) {
                        sum = INT_MAX;
                        break;
                    }
                    sum +=mincost[i];
                }
            ans = min(ans, sum);
        } while(next_permutation(v.begin(), v.end()));

        if(ans == INT_MAX) cout << -1 << endl;
        else cout << ans << endl;
    }
    return 0;
}
