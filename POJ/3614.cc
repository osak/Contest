//Name: Sunscreen
//Level: 2
//Category: 貪欲,Greedy
//Note:

/**
 * SPF値の小さいローションから先に消費していく。
 * このとき、割り当てる牛はなるべく右端が小さいものから消費していくと良い。
 * （右端が大きいものは、後で他のローションを割り当てられる可能性があるため）
 *
 * オーダーはO(C log C + L)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

bool solve() {
    int C, L;
    if(scanf("%d %d", &C, &L) == EOF) return false;

    static pair<int,int> cows[2500];
    TIMES(i, C) {
        scanf("%d %d", &cows[i].first, &cows[i].second);
    }
    sort(cows, cows+C);
    static pair<int,int> lotions[2500];
    TIMES(i, L) {
        scanf("%d %d", &lotions[i].first, &lotions[i].second);
    }
    sort(lotions, lotions+L);

    priority_queue<int> q;
    int ans = 0;
    int pos = 0;
    TIMES(i, L) {
        const int spf = lotions[i].first;
        while(pos < C && cows[pos].first <= spf) {
            q.push(-cows[pos].second);
            ++pos;
        }
        int cnt = 0;
        while(!q.empty() && cnt < lotions[i].second) {
            const int r = -q.top();
            q.pop();
            if(r >= spf) {
                ++cnt;
            }
        }
        ans += cnt;
    }
    printf("%d\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
