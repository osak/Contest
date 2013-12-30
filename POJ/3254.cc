//Name: Corn Fields
//Level: 3
//Category: 動的計画法,DP,bitDP
//Note:

/**
 * 各行の配置は、直前の行の配置のみに制限される。
 * 直前の行の配置は高々2^12通りしかないので、メモ化することで状態数はO(M 2^N)通りになる。
 *
 * オーダーはO(M 4^N)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

typedef long long LL;
const LL MOD = 100000000;

int mask_of[12];
LL memo[12][1<<12];
int M, N;

LL calc(int row, int prev_pat) {
    if(row == M) return 1;

    LL &res = memo[row][prev_pat];
    if(res >= 0) return res;
    res = 0;
    TIMES(pat, 1<<N) {
        if((mask_of[row] & pat) != pat) continue;
        if(pat & prev_pat) continue;
        bool ok = true;
        TIMES(i, N) {
            if((pat & (3<<i)) == (3<<i)) ok = false;
        }
        if(!ok) continue;
        res += calc(row+1, pat);
        res %= MOD;
    }
    return res;
}

bool solve() {
    if(scanf("%d %d", &M, &N) == EOF) return false;
    if(!M && !N) return false;
    TIMES(i, M) {
        TIMES(j, N) {
            int v;
            scanf("%d", &v);
            mask_of[i] |= v << j;
        }
    }
    TIMES(i, M) {
        TIMES(j, 1<<N) {
            memo[i][j] = -1;
        }
    }
    printf("%lld\n", calc(0, 0));
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
