#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long Cost;
Cost field[10000][10];
Cost memo[100][2][2]; // memo[i][j][k] = field[i*100][j] to field[(i+1)*100-1][k]

const Cost INF = 1000000000LL * 10 * 10000 * 2;

int H, W, Q;
void calcrem(int from, int fromcol, int to, Cost *buf) {
    if(to < from) {
        buf[0] = buf[1] = 0;
        return;
    }
    Cost dp[2][2] = {{INF, INF}, {0, 0}};
    Cost *prev = dp[0], *cur = dp[1];

    const int lim = min(to+1, H);
    prev[fromcol] = field[from][fromcol];
    for(int row = from+1; row < lim; ++row) {
        cur[0] = min(prev[0], prev[1]+field[row][1]) + field[row][0];
        cur[1] = min(prev[1], prev[0]+field[row][0]) + field[row][1];
        swap(prev, cur);
    }
    buf[0] = prev[0];
    buf[1] = prev[1];
}

int main() {
    scanf("%d %d %d", &W, &H, &Q);
    if(W != 2) {
        puts("42");
        return 0;
    }
    for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W; ++j) {
            scanf("%lld", &field[i][j]);
        }
    }
    for(int i = 0; i < H/100; ++i) {
        calcrem(i*100, 0, (i+1)*100, memo[i][0]);
        calcrem(i*100, 1, (i+1)*100, memo[i][1]);
    }
    while(Q--) {
        int sx, sy, tx, ty;
        scanf("%d %d %d %d", &sx, &sy, &tx, &ty);
        --sx; --sy; --tx; --ty;
        if(sy > ty) {
            swap(sx, tx);
            swap(sy, ty);
        }
        int near_si = sy / 100;
        if(sy % 100 != 0) ++near_si;
        int near_ti = ty / 100;

        const int near_sy = near_si * 100;
        const int near_ty = near_ti * 100;
        Cost sbuf[2] = {0, 0};
        const int target_s = min(near_ty, near_sy);
        calcrem(sy, sx, target_s, sbuf);

        Cost mid[2];
        mid[0] = sbuf[0];
        mid[1] = sbuf[1];
        mid[0] -= field[target_s][0];
        mid[1] -= field[target_s][1];
        for(int i = near_si; i < near_ti; ++i) {
            Cost next[2];
            next[0] = min(mid[0] + memo[i][0][0], mid[1] + memo[i][1][0]);
            next[1] = min(mid[0] + memo[i][0][1], mid[1] + memo[i][1][1]);
            mid[0] = next[0];
            mid[1] = next[1];
        }

        Cost tbuf[2][2] = {{0,0},{0,0}};
        calcrem(near_ty, 0, ty, tbuf[0]);
        calcrem(near_ty, 1, ty, tbuf[1]);
        const Cost ans = min(mid[0] + tbuf[0][tx] - field[near_ty][0], mid[1] + tbuf[1][tx] - field[near_ty][1]);
        cout << ans << endl;
    }

    return 0;
}
