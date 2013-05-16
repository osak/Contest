//Name: The Fewest Coins
//Level: 4
//Category: DP,動的計画法,個数制限付きDP
//Note:

/*
 * 枚数制限付きとなしで2つ，ある金額を作るのに必要な最小枚数のテーブルを作る．
 * 枚数制限付きのほうは，枚数c_iを
 *   c_i = 1 + 2 + 4 + …… + 2^(floor(log c_i)) + rem
 * と分解し，価値v_i*1, v_i*2, ……のコインが1枚ずつあるものとしてDP．
 *
 * 支払額上限はT*2くらいである．
 * (2T以上払うとき，お釣りはT以上だが，コインの最大額がT以下であれば必ず1枚は同じ物が返ってくるはず)
 * オーダーは O(T * N log C) 程度．
 * ただし C = max(c_i)．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

const int INF = 10000*100*10;
const int LIM = 10000*2;
int dp_lim[10000*2+1], dp_nolim[10000*2+1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, T;
    while(cin >> N >> T) {
        vector<int> vs(N), cs(N);
        TIMES(i, N) {
            cin >> vs[i];
        }
        TIMES(i, N) {
            cin >> cs[i];
        }

        const int UBOUND = LIM+1;
        fill_n(dp_lim, UBOUND, INF);
        fill_n(dp_nolim, UBOUND, INF);
        dp_lim[0] = 0;
        // Make limited table (for payment)
        TIMES(i, N) {
            int k = 1;
            int num = cs[i];
            const int v = vs[i];
            while(k <= num) {
                for(int val = UBOUND-1; val >= 0; --val) {
                    if(val-v*k < 0) break;
                    dp_lim[val] = min(dp_lim[val], dp_lim[val-v*k]+k);
                }
                num -= k;
                k *= 2;
            }
            if(num > 0) {
                for(int val = UBOUND-1; val >= 0; --val) {
                    if(val-v*num < 0) break;
                    dp_lim[val] = min(dp_lim[val], dp_lim[val-v*num]+num);
                }
            }
        }

        // Make unlimited table (for change)
        dp_nolim[0] = 0;
        TIMES(i, N) {
            const int v = vs[i];
            for(int val = v; val < UBOUND; val += v) {
                dp_nolim[val] = min(dp_nolim[val], dp_nolim[val-v]+1);
            }
        }

        int ans = INF;
        for(int val = T; val < UBOUND; ++val) {
            ans = min(ans, dp_lim[val] + dp_nolim[val-T]);
            //cout << val << ' ' << dp_lim[val] << ' ' << dp_nolim[val-T] << endl;
        }
        if(ans == INF) ans = -1;
        cout << ans << endl;
    }
    return 0;
}
