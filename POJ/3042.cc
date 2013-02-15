//Name: Grazing on the Run
//Level: 4
//Category: 動的計画法,DP
//Note:

/*
 * Lを含む範囲で草を食べていくので，食べた範囲の両端と，左右どちらにいるかのみ管理すればよい．
 * 管理する値は(dir,[left,right])を食べ尽くした時点でかかることが確定しているスコア．
 * つまり，
 *   dp[0][l][r] = min(dp[0][l+1][r] + dist(l+1,l)*(N-(r-l)), dp[1][l+1][r] + dist(r,l)*(N-(r-l)))
 *   dist(a,b) = clump[a]-clump[b]
 * etc.
 * 要するに，最初の草を食べるまで10単位の時間がかかったのなら，N*10でスコアに響くということ．
 *
 * オーダーは O(N^2)．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)

long long dp[2][1001][1001];
int clumps[1001];
int N, L;

const long long INF = std::numeric_limits<long long>::max()/2;

long long calc(int pos, int left, int right) {
    long long &ref = dp[pos][left][right];
    if(ref == -1) {
        ref = INF;
        if(clumps[left] <= L && L <= clumps[right]) {
            if(left == right) {
                ref = 0;
            } else {
                const long long dist = N-(right-left);
                if(pos == 0) {
                    if(left+1 < N) ref = calc(0, left+1, right)+(clumps[left+1]-clumps[left])*dist;
                    ref = min(ref, calc(1, left+1, right)+(clumps[right]-clumps[left])*dist);
                } else {
                    if(right-1 >= 0) ref = calc(1, left, right-1)+(clumps[right]-clumps[right-1])*dist;
                    ref = min(ref, calc(0, left, right-1)+(clumps[right]-clumps[left])*dist);
                }
            }
        }
    }
    return ref;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> L;
    bool has_start = false;
    for(int i = 0; i < N; ++i) {
        cin >> clumps[i];
        if(clumps[i] == L) has_start = true;
    }
    if(!has_start) clumps[N++] = L;
    sort(clumps, clumps+N);
    for(int k = 0; k < 2; ++k)
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                dp[k][i][j] = -1;
    cout << min(calc(0,0,N-1), calc(1,0,N-1)) << endl;
    return 0;
}
