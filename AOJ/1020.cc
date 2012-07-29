//Name: Cleaning Robot
//Level: 2
//Category: 全探索,確率,メモ化再帰
//Note:

/*
 * 最大4方向に移動 ** 最大15回移動 = 約10億。
 * しかし、状態変数はバッテリー16*X座標3*Y座標3 = 144通りしかないので、メモつきDFSで解ける。
 */
#include <iostream>
#include <cstdio>
#include <utility>

using namespace std;

void decode(char c, int &x, int &y) {
    x = (c-'A')/3;
    y = (c-'A')%3;
}

const int d[4][2] = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}
};

pair<int,int> memo[16][3][3];
pair<int, int> dfs(int n, int x, int y, int tx, int ty, int bx, int by) {
    if(memo[n][x][y].first != -1) return memo[n][x][y];

    if(x == bx && y == by) return memo[n][x][y] = make_pair(0, 1);
    if(n == 0) {
        if(x == tx && y == ty) return memo[n][x][y] = make_pair(1, 1);
        else return memo[n][x][y] = make_pair(0, 1);
    }
    pair<int, int> cnt = make_pair(0, 0);
    for(int i = 0; i < 4; ++i) {
        int nx = x + d[i][0];
        int ny = y + d[i][1];
        pair<int,int> tmp;
        if(nx < 0 || 3 <= nx || ny < 0 || 3 <= ny || (nx == bx && ny == by)) tmp = dfs(n-1, x, y, tx, ty, bx, by);
        else tmp = dfs(n-1, nx, ny, tx, ty, bx, by);
        cnt.first += tmp.first;
        cnt.second += tmp.second;
    }
    return memo[n][x][y] = cnt;
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;
        char S, T, B;
        cin >> S >> T >> B;

        int x, y;
        int tx, ty;
        int bx, by;
        decode(S, x, y);
        decode(T, tx, ty);
        decode(B, bx, by);

        for(int i = 0; i <= 15; ++i)
            for(int j = 0; j < 3; ++j)
                for(int k = 0; k < 3; ++k)
                    memo[i][j][k] = make_pair(-1, -1);
        pair<int, int> cnt = dfs(N, x, y, tx, ty, bx, by);
        printf("%.10f\n", (double)cnt.first / cnt.second);
    }
}
