//Name: VOCAL ANDROID
//Level: 2
//Category: DP,動的計画法
//Note:

/*
 * フレーズの長さは高々393通りなので、それぞれの長さで得られる最高得点だけ覚えておけばよい。
 * これを使って、ある長さのメロディで得られる最高得点についてDPする。
 *
 * オーダーはO(NML)、ただしLは最大のフレーズ長。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define TIMES(i,n) for(int i = 0; i < (n); ++i)

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    while(cin >> N) {
        vector<int> phrases(394, 0);
        int maxlen = 0;
        TIMES(i, N) {
            int S, L, P;
            cin >> S >> L >> P;
            for(int l = S; l <= L; ++l) {
                phrases[l] = max(phrases[l], P);
            }
            maxlen = max(maxlen, L);
        }
        int M;
        cin >> M;
        vector<int> WS(M);
        TIMES(i, M) {
            cin >> WS[i];
        }
        vector<int> ans;
        FOREACH(it, WS) {
            const int W = *it;
            vector<int> dp(W+1, 0);
            TIMES(pos, W) {
                TIMES(len, maxlen+1) {
                    const int next = pos+len;
                    if(next > W) break;
                    dp[next] = max(dp[next], dp[pos]+phrases[len]);
                }
            }
            if(dp[W] == 0) {
                ans.clear();
                ans.push_back(-1);
                break;
            } else {
                ans.push_back(dp[W]);
            }
        }
        FOREACH(it, ans) {
            cout << *it << endl;
        }
    }
    return 0;
}
