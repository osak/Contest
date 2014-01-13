//Name: Knapsack II
//Level: 4
//Category: 動的計画法,DP,ダイクストラ,Dijkstra
//Note:

/**
 * 最も小さい荷物の大きさをv0としてmod v0で考えると、
 * ある容量 v = a*v0 + r が充填可能なとき、 v = (a+1)*v0 + r も充填可能である。
 * このようなaで最小のものは、最短経路問題と同様の方法で求めることができる。
 * 充填不可能な最大の容量は、もっとも大きいvに対して(v-5000, v)の範囲にあるため、大きい方から試していくことで得られる。
 *
 * オーダーはO(Nv0 log v0 + v0^2)。
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
    int N;
    if(scanf("%d", &N) == EOF) return false;
    if(!N) return false;

    static int vs[500];
    TIMES(i, N) {
        scanf("%d", &vs[i]);
    }
    sort(vs, vs+N);

    static int memo[5050];
    fill_n(memo, vs[0], -1);
    priority_queue<int> q;
    q.push(0);
    memo[0] = 0;
    while(!q.empty()) {
        const int val = -q.top();
        q.pop();
        if(val > memo[val % vs[0]]) continue;
        TIMES(i, N) {
            const int next = val + vs[i];
            const int idx = next % vs[0];
            if(memo[idx] == -1 || next < memo[idx]) {
                memo[idx] = next;
                q.push(-next);
            }
        }
    }
    int ans = -1;
    TIMES(i, vs[0]) {
        if(memo[i] == -1) {
            ans = -1;
            break;
        } else {
            ans = max(ans, memo[i]-1);
        }
    }
    if(ans != -1) {
        while(true) {
            bool updated = false;
            TIMES(i, vs[0]) {
                if(memo[ans % vs[0]] <= ans) {
                    --ans;
                    updated = true;
                }
            }
            if(!updated) break;
        }
    }
    if(ans == -1) {
        puts("INF");
    } else {
        printf("%d\n", ans);
    }
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
