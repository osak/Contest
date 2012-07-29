//Name: A Thief
//Level: 2
//Category: 動的計画法,DP
//Note:

/*
 * 使う品物の上限と重さをindexにしてDPすればよい。
 */
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
    for(int CASE = 1; ; ++CASE) {
        int W;
        cin >> W;
        if(!W) break;

        int N;
        cin >> N;
        vector<pair<int, int> > v;
        for(int i = 0; i < N; ++i) {
            int val, w;
            char comma;
            cin >> val >> comma >> w;
            v.push_back(make_pair(val, w));
        }

        vector<vector<int> > dp(2, vector<int>(W+1, 0));
        int vn = 0;
        int mv = 0;
        for(int i = 0; i < N; ++i) {
            vector<int> &vec = dp[vn];
            vector<int> &prev = dp[1-vn];

            for(int w = 0; w <= W; ++w) {
                int pw = w - v[i].second;
                vec[w] = prev[w];
                if(pw >= 0) {
                    vec[w] = max(vec[w], prev[pw] + v[i].first);
                    mv = max(mv, vec[w]);
                }
            }
            vn = 1-vn;
        }

        cout << "Case " << CASE << ":" << endl;
        for(int w = 0; w <= W; ++w) {
            if(dp[1-vn][w] == mv) {
                cout << mv << endl;
                cout << w << endl;
                break;
            }
        }
    }
    return 0;
}
