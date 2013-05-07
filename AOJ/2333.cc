//Name: My friends are small
//Level: 4
//Category: 動的計画法,DP
//Note:

/*
 * 入力をあらかじめ昇順にソートしておき，解を
 *   ∑ v[0...i]を全部使い，v[i]を飛ばしてv[i+1...N]を条件を満たすように選ぶパターン数
 * で求める．
 * ここで，条件を満たすパターンとは，sum_i = ∑ v[0...i] として
 *   W - sum_i - w < v[i]
 * すなわち
 *   w > W - sum_i - v[i]
 * であるwを構成できるパターンである．
 * このようなwの構成の個数は，後ろからDPすることで求められる．
 *
 * オーダーは O(NW)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

typedef long long LL;
const LL MOD = 1000000007;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, W;
    while(cin >> N >> W) {
        //dp[i][w] = v[i...N]でwを作るパターン数
        vector<vector<LL> > dp(N+1, vector<LL>(10001, 0));
        vector<int> v(N);
        TIMES(i, N) {
            cin >> v[i];
        }
        sort(v.begin(), v.end());

        dp[N][0] = 1;
        for(int i = N-1; i >= 0; --i) {
            dp[i] = dp[i+1];
            TIMES(w, W+1) {
                if(w < v[i]) continue;
                dp[i][w] += dp[i+1][w-v[i]];
                dp[i][w] %= MOD;
            }
        }

        /*
        TIMES(i, N) {
            TIMES(w, W) {
                cout << dp[i][w] << ' ';
            }
            cout << endl;
        }
        */

        LL ans = 0;
        int sum = 0;
        TIMES(i, N) {
            // skip v[i]
            const int remain = W - sum;
            for(int w = max(0, W-sum-v[i]+1); w <= remain; ++w) {
                ans += dp[i+1][w];
                ans %= MOD;
            }
            sum += v[i];
            if(sum > W) break;
        }
        // use all
        if(sum <= W) {
            ans += 1;
            ans %= MOD;
        }
        cout << ans << endl;
    }
    return 0;
}
