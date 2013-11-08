//Name: Common Subsequence
//Level: 2
//Category: 動的計画法,DP,文字列,Longest Common Subsequence,LCS
//Note:

/**
 * 典型的なLCS問題。
 *   dp[i][j] = A[0..i], B[0..j]の最長LCS長
 * として、A[i] == B[j]のときに加算する。
 *
 * オーダーはO(|A||B|)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

inline void update(int &var, int val) {
    if(val > var) var = val;
}

bool solve() {
    string A, B;
    if(!(cin >> A >> B)) return false;
    vector<vector<int> > dp(A.size(), vector<int>(B.size(), 0));
    for(int i = 0; i < A.size(); ++i) {
        for(int j = 0; j < B.size(); ++j) {
            int step = A[i] == B[j];
            update(dp[i][j], i > 0 ? dp[i-1][j] : 0);
            update(dp[i][j], j > 0 ? dp[i][j-1] : 0);
            update(dp[i][j], ((i > 0 && j > 0) ? dp[i-1][j-1] : 0) + step);
        }
    }
    cout << dp[A.size()-1][B.size()-1] << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(solve()) ;
    return 0;
}
