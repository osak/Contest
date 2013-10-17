//Name: Meteor Shower
//Level: 2
//Category: シミュレーション,幅優先探索,BFS,動的計画法,DP
//Note:

/**
 * 1ターンごとに隕石が落ちてくるシミュレーションを行いながら、各マスに辿り着いた最速時間を覚えておく。
 * 各ターンでは、潰れていないマスから前後左右に1歩歩き、上の表を更新していく。
 * 全ての隕石が落ちても潰れていないマスが解の候補となる。
 *
 * オーダーはO(NT + M)。
 * ただしN = 303（グリッドのマス数）。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

bool in_range(int a, int x, int b) {
    return a <= x && x < b;
}

struct Tag {
    int x, y;
    int t;
    Tag() {}
    Tag(int x, int y, int t) : x(x), y(y), t(t) {}

    bool operator <(const Tag &other) const {
        return t < other.t;
    }
};

const int DX[] = {1, 0, -1, 0};
const int DY[] = {0, -1, 0, 1};
const int INF = 10000;

int dp[2][303][303];
Tag meteors[50000];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int M;
    scanf("%d", &M);
    TIMES(i, 303) {
        TIMES(j, 303) {
            dp[0][i][j] = INF;
            dp[1][i][j] = INF;
        }
    }
    TIMES(i, M) {
        Tag &meteor = meteors[i];
        scanf("%d %d %d", &meteor.x, &meteor.y, &meteor.t);
    }
    sort(meteors, meteors+M);
    int pos = 0;
    dp[0][0][0] = 0;
    while(pos < M && meteors[pos].t == 0) {
        dp[1][meteors[pos].x][meteors[pos].y] = -1;
        for(int d = 0; d < 4; ++d) {
            const int ax = meteors[pos].x + DX[d];
            const int ay = meteors[pos].y + DY[d];
            if(in_range(0, ax, 303) && in_range(0, ay, 303)) {
                dp[1][ax][ay] = -1;
            }
        }
        ++pos;
    }

    for(int turn = 1; turn <= meteors[M-1].t+1; ++turn) {
        while(pos < M && meteors[pos].t == turn) {
            dp[1][meteors[pos].x][meteors[pos].y] = -1;
            for(int d = 0; d < 4; ++d) {
                const int ax = meteors[pos].x + DX[d];
                const int ay = meteors[pos].y + DY[d];
                if(in_range(0, ax, 303) && in_range(0, ay, 303)) {
                    dp[1][ax][ay] = -1;
                }
            }
            ++pos;
        }

        for(int x = 0; x < 303; ++x) {
            for(int y = 0; y < 303; ++y) {
                if(dp[0][x][y] == -1 || dp[0][x][y] == INF) continue;
                for(int d = 0; d < 4; ++d) {
                    const int nx = x + DX[d];
                    const int ny = y + DY[d];
                    if(in_range(0, nx, 303) && in_range(0, ny, 303)) {
                        dp[1][nx][ny] = min(dp[1][nx][ny], dp[0][x][y]+1);
                    }
                }
            }
        }

        for(int x = 0; x < 303; ++x) {
            for(int y = 0; y < 303; ++y) {
                dp[0][x][y] = dp[1][x][y];
            }
        }
    }
    int ans = INF;
    for(int x = 0; x < 303; ++x) {
        for(int y = 0; y < 303; ++y) {
            //if(dp[0][x][y] != INF) printf("%d %d %d\n", x, y, dp[0][x][y]);
            if(dp[0][x][y] != -1) ans = min(ans, dp[0][x][y]);
        }
    }
    if(ans == INF) ans = -1;
    printf("%d\n", ans);
    return 0;
}
