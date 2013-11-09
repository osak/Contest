//Name: Aggressive cows
//Level: 2
//Category: 二分探索
//Note:

/**
 * 最低間隔をひとつ決めた時、牛の配置は左からGreedyに取ればよいことがわかる。
 * (Greedyでない配置が得られた時、最初にGreedyでなくなった箇所を左にずらしても
 * 結果は変わらないため）。
 * 次に配置する箇所は二分探索で求められる。
 * これを、最低間隔に関して二分探索すればよい。
 *
 * オーダーはO(N (log N)^2)。
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

int stalls[100000];

bool solve() {
    int N, C;
    if(scanf("%d %d", &N, &C) == EOF) return false;
    for(int i = 0; i < N; ++i) {
        scanf("%d", stalls+i);
    }
    sort(stalls, stalls+N);
    int left = 0, right = stalls[N-1]+1;
    while(left+1  < right) {
        int center = (left+right) / 2;
        int *cur = stalls;
        bool ok = true;
        for(int i = 1; i < C; ++i) {
            int *next = lower_bound(cur+1, stalls+N, *cur + center);
            if(next == stalls+N) {
                ok = false;
                break;
            }
            cur = next;
        }
        if(ok) left = center;
        else right = center;
    }
    printf("%d\n", left);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
