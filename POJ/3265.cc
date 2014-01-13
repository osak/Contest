//Name: Problem Solving
//Level: 2
//Category: 動的計画法,DP,幅優先探索,BFS
//Note:

/**
 * 問題が解決した次の月に後金を払うので、一月の支払いは(前金+前月の後金)で表せる。
 * すなわち、前月と今月でどこまで問題が解決されているかを状態として持っておけばよい。
 * これをDPやBFS形式で書く。
 *
 * オーダーはO(P^3)。
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

int before[300], after[300];
bool memo[301][301];

inline int get(int *buf, int pos) {
    if(pos < 0) return 0;
    return buf[pos];
}

bool solve() {
    int P, M;
    if(scanf("%d %d", &M, &P) == EOF) return false;
    if(!P && !M) return false;

    TIMES(i, P) {
        int b, a;
        scanf("%d %d", &b, &a);
        if(i > 0) {
            before[i] = before[i-1];
            after[i] = after[i-1];
        }
        before[i] += b;
        after[i] += a;
    }
    TIMES(i, P) {
        TIMES(j, P) {
            memo[i][j] = false;
        }
    }

    vector<pair<int,int> > q[2];
    q[0].push_back(make_pair(-1, -1));
    int turn = 2;
    for(; q[0].size() > 0; ++turn) {
        const int N = q[0].size();
        q[1].clear();
        TIMES(i, N) {
            const pair<int,int> cur = q[0][i];
            const int ap = get(after, cur.second) - get(after, cur.first-1);
            if(cur.second == P-1 && ap <= M) {
                goto end;
            }
            for(int j = cur.second; j < P; ++j) {
                int bp = get(before, j) - get(before, cur.second);
                if(ap+bp > M) break;
                if(memo[cur.second+1][j]) continue;
                memo[cur.second+1][j] = true;
                q[1].push_back(make_pair(cur.second+1, j));
            }
        }
        q[0].swap(q[1]);
    }
end:
    printf("%d\n", turn);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
