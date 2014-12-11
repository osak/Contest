//Name: A-B Problem
//Level: 2
//Category: 動的計画法,DP
//Note:

/**
 * dp[n][k][b] = n桁目以降で、あとk回まで繰り下がりを忘れていい時に作れる最大値（ただしn桁目におけるborrowの値はb）
 * として、メモ化再帰の形で書く。
 *
 * オーダーは O(K log A)。
 */
#include <iostream>
#include <string>
#include <array>
#include <algorithm>

using namespace std;

template <typename T>
struct Maybe {/*{{{*/
    T val;
    bool valid;

    Maybe() : valid(false) {}
    Maybe(T &t) : val(t), valid(true) {}

    T& operator =(const T &rv) {
        val = rv;
        valid = true;
        return val;
    }
};/*}}}*/

string A, B;
array<array<array<Maybe<int>,2>,10>,10> memo;
int solve(int n, int k, int b) {
    if(n >= A.size()) return 0;
    if(memo[n][k][b].valid) return memo[n][k][b].val;
    const int av = A[n] - '0';
    const int bv = n < B.size() ? B[n] - '0' : 0;

    int ans = 0;
    // consider borrow
    {
        int rem = av - b;
        if(rem >= bv) {
            ans = solve(n+1, k, 0) * 10 + (rem - bv);
        } else {
            ans = solve(n+1, k, 1) * 10 + (rem + 10 - bv);
        }
    }
    // ignore borrow
    if(b > 0 && k > 0) {
        if(av >= bv) {
            ans = max(ans, solve(n+1, k-1, 0) * 10 + (av - bv));
        } else {
            ans = max(ans, solve(n+1, k-1, 1) * 10 + (av + 10 - bv));
        }
    }
    memo[n][k][b] = ans;
    return ans;
}

bool solve() {
    int K;
    if(!(cin >> A >> B >> K)) return false;
    reverse(begin(A), end(A));
    reverse(begin(B), end(B));

    for(int n = 0; n < 10; ++n) {
        for(int k = 0; k <= K; ++k) {
            for(int b = 0 ; b < 2; ++b) {
                memo[n][k][b].valid = false;
            }
        }
    }

    cout << solve(0, K, 0) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
