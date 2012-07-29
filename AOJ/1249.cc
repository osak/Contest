#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

char field[7][7][7];
int dp[7][7][7][13];
int N;

char get(int x, int y, int z) {
    if(x < 0 || N <= x || y < 0 || N <= y || z < 0 || N <= z) return '.';
    return field[x][y][z];
}

int dpget(int x, int y, int z, int d) {
    if(x < 0 || N <= x || y < 0 || N <= y || z < 0 || N <= z) return 0;
    return dp[x][y][z][d];
}

int main() {
    ios::sync_with_stdio(0);
    while(true) {
        int M, P;
        cin >> N >> M >> P;
        if(!N && !M && !P) break;

        memset(field, '.', sizeof(field));

        int winturn = 0;
        string winner = "Draw";
        for(int turn = 1; turn <= P; ++turn) {
            int x, y;
            cin >> x >> y;
            --x; --y;
            for(int depth = 0; depth < N; ++depth) {
                if(field[x][y][depth] == '.') {
                    field[x][y][depth] = turn%2 == 1 ? 'B' : 'W';
                    break;
                }
            }
            if(winturn != 0) continue;

            bool win = false;
            memset(dp, 0, sizeof(dp));
            for(int z = 0; z < N; ++z) {
                for(int y = 0; y < N; ++y) {
                    for(int x = 0; x < N; ++x) {
                        char peg = get(x, y, z);
                        char color = turn%2 == 1 ? 'B' : 'W';
                        if(peg != color) continue;

                        dp[x][y][z][0]  = dpget(x-1, y, z, 0)+1;
                        dp[x][y][z][1]  = dpget(x, y-1, z, 1)+1;
                        dp[x][y][z][2]  = dpget(x, y, z-1, 2)+1;

                        dp[x][y][z][3]  = dpget(x-1, y, z-1, 3)+1;
                        dp[x][y][z][4]  = dpget(x+1, y, z-1, 4)+1;
                        dp[x][y][z][5]  = dpget(x, y+1, z-1, 5)+1;
                        dp[x][y][z][6]  = dpget(x, y-1, z-1, 6)+1;
                        dp[x][y][z][7]  = dpget(x-1, y-1, z, 7)+1;
                        dp[x][y][z][8]  = dpget(x+1, y-1, z, 8)+1;

                        dp[x][y][z][9]  = dpget(x-1, y-1, z-1, 9)+1;
                        dp[x][y][z][10] = dpget(x+1, y-1, z-1, 10)+1;
                        dp[x][y][z][11] = dpget(x-1, y+1, z-1, 11)+1;
                        dp[x][y][z][12] = dpget(x+1, y+1, z-1, 12)+1;

                        for(int i = 0; i < 13; ++i) {
                            //cout << dp[x][y][z][i] << endl;
                            if(dp[x][y][z][i] >= M) win = true;
                        }
                    }
                }
            }

            if(win) {
                winner = turn%2 == 1 ? "Black" : "White";
                winturn = turn;
            }
        }

        if(winturn != 0) {
            cout << winner << ' ' << winturn << endl;
        }
        else {
            cout << winner << endl;
        }
    }

    return 0;
}
