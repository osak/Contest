//Name: Yogurt factory
//Level: 2
//Category: DP,動的計画法
//Note:

/**
 * i週目の単位生産コストは、min(c_j + S×(i-j))で計算できる。
 * これはDPによって求められる。
 *
 * オーダーはO(N)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

bool solve() {
    int N, S;
    if(scanf("%d %d", &N, &S) == EOF) return false;

    long long ans = 0;
    int cost = 500000;
    while(N--) {
        int c, y;
        scanf("%d %d", &c, &y);
        cost = min(cost+S, c);
        ans += (long long)cost * y;
    }
    cout << ans << endl;
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
