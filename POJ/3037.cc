//Name: Skiing
//Level: 3
//Category: グラフ,Graph,最短経路,Special Judge
//Note: 明記されてないが、浮動小数点数の誤差判定が適用される。

/**
 * あるマスに行った時の係数は、経路にかかわらず左上のマスとの差分になる。
 * したがって、普通にDijkstraなどで最短経路を求める。
 *
 * オーダーはO(RC log RC)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

struct Tag {
    double t;
    int r, c;

    Tag() {}
    Tag(const double &t, int r, int c) : t(t), r(r), c(c) {}

    bool operator <(const Tag &other) const {
        return other.t < t;
    }
};

int E[100][100];
bool visited[100][100];
double dp[100][100];
double speed_inv[100][100];

bool solve() {
    int V, R, C;
    if(scanf("%d %d %d", &V, &R, &C) == EOF) return false;
    if(!V && !R && !C) return false;
    TIMES(r, R) {
        TIMES(c, C) {
            scanf("%d", &E[r][c]);
            const int p = E[0][0] - E[r][c];
            speed_inv[r][c] = 1.0 / (V * pow(2.0, p));
            visited[r][c] = false;
        }
    }

    if(R == 1 && C == 1) {
        puts("0.00");
        return true;
    }
    priority_queue<Tag> q;
    q.push(Tag(0, 0, 0));
    visited[0][0] = true;
    dp[0][0] = 0;
    while(!q.empty()) {
        double t = q.top().t;
        const int cur_r = q.top().r;
        const int cur_c = q.top().c;
        q.pop();
        if(dp[cur_r][cur_c] < t) continue;
        if(cur_r == R-1 && cur_c == C-1) {
            printf("%.2f\n", t);
            break;
        }
        static const int DR[] = {0, -1, 0, 1};
        static const int DC[] = {1, 0, -1, 0};
        double nt = t;
        nt += speed_inv[cur_r][cur_c];
        TIMES(dir, 4) {
            const int nr = cur_r + DR[dir];
            const int nc = cur_c + DC[dir];
            if(nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if(visited[nr][nc] && (dp[nr][nc] < nt || dp[nr][nc] == nt)) continue;
            visited[nr][nc] = true;
            dp[nr][nc] = nt;
            q.push(Tag(nt, nr, nc));
        }
    }
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
