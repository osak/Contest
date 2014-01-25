//Name: Making the Grade
//Level: 3
//Category: 動的計画法,DP
//Note:

/**
 * 高さは入力で与えられた高さ以外は考えなくてよい。
 *
 * 単調非減少列にするとき、それぞれの地点の高さh[i]を決めると、直前の状態は0～h[i]のうち最小コストで実現できるものを選べばよい。
 * これはO(N)で求められる。
 * 単調非増加列についても同様。
 *
 * オーダーはO(N^2)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

const int INF = INT_MAX;
int hlist[2000];
int *hend;

bool solve() {
    int N;
    if(scanf("%d", &N) == EOF) return false;

    static int h[2000];
    TIMES(i, N) {
        scanf("%d", h+i);
        hlist[i] = h[i];
    }
    sort(hlist, hlist+N);
    hend = unique(hlist, hlist+N);
    const int K = hend - hlist;
    
    static int dp[2][2000];
    // non-decreasing
    int cur = 0;
    fill_n(dp[cur^1], K, 0);
    TIMES(i, N) {
        int min_cost = INF;
        TIMES(j, K) {
            min_cost = min(min_cost, dp[cur^1][j]);
            dp[cur][j] = min_cost + abs(hlist[j] - h[i]);
        }
        cur ^= 1;
    }
    int ans = *min_element(dp[cur^1], &dp[cur^1][K]);

    // non-increasing
    cur = 0;
    fill_n(dp[cur^1], K, 0);
    TIMES(i, N) {
        int min_cost = INF;
        for(int j = K-1; j >= 0; --j) {
            min_cost = min(min_cost, dp[cur^1][j]);
            dp[cur][j] = min_cost + abs(hlist[j] - h[i]);
        }
        cur ^= 1;
    }
    ans = min(ans, *min_element(dp[cur^1], &dp[cur^1][K]));
    printf("%d\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
