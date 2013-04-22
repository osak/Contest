//Name: X-factor Chains
//Level: 2
//Category: 約数,DP,動的計画法
//Note:

/*
 * Xの約数を全部求めてから，i番目の約数を最後に置くような列の最長長さとパターン数をDPで求める．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

int dp[10000];
int cnt[10000];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int X;
    while(cin >> X) {
        const int lim = sqrt(X);
        vector<int> divisors;
        for(int i = 1; i <= lim; ++i) {
            if(X % i == 0) {
                divisors.push_back(i);
                divisors.push_back(X / i);
            }
        }
        sort(divisors.begin(), divisors.end());
        divisors.erase(unique(divisors.begin(), divisors.end()), divisors.end());
        const int N = divisors.size();
        fill_n(dp, N, 0);
        fill_n(cnt, N, 0);
        dp[0] = 1;
        cnt[0] = 1;
        TIMES(i, N) {
            TIMES(j, i) {
                if(divisors[i] % divisors[j] == 0) {
                    if(dp[i] == dp[j]+1) {
                        cnt[i] += cnt[j];
                    } else if(dp[i] < dp[j]+1) {
                        dp[i] = dp[j]+1;
                        cnt[i] = cnt[j];
                    }
                }
            }
        }
        cout << dp[N-1]-1 << ' ' << cnt[N-1] << endl;
        //cout << X << endl;
    }
    return 0;
}
