#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int H, W;
    long long L;
    while (cin >> H >> W >> L && H != 0) {
        vector<string> grid(H);
        pair<int,int> pos;
        int dir;
        for (int i = 0; i < H; i++) {
            cin >> grid[i];
            for (int j = 0; j < W; j++) {
                if (grid[i][j] == 'N') {
                    pos = make_pair(i, j);
                    grid[i][j] = '.';
                    dir = 0;
                } else if (grid[i][j] == 'E') {
                    pos = make_pair(i, j);
                    grid[i][j] = '.';
                    dir = 1;
                } else if (grid[i][j] == 'S') {
                    pos = make_pair(i, j);
                    grid[i][j] = '.';
                    dir = 2;
                } else if (grid[i][j] == 'W') {
                    pos = make_pair(i, j);
                    grid[i][j] = '.';
                    dir = 3;
                }
            }
        }

        vector<vector<vector<long long> > > ts(H, vector<vector<long long> >(W, vector<long long>(4, -1)));
        static const int di[] = {-1, 0, 1, 0};
        static const int dj[] = {0, 1, 0, -1};
        ts[pos.first][pos.second][dir] = 0;
        long long rest = -1;
        for (long long i = 0LL; i < L;) {
            const int k = pos.first + di[dir];
            const int l = pos.second + dj[dir];
            if (0 <= k && k < H && 0 <= l && l < W && grid[k][l] != '#') {
                ++i;
                if (ts[k][l][dir] != -1) {
                    const long long gap = i - ts[k][l][dir];
                    rest = (L - ts[k][l][dir])%gap;
                    break;
                } else {
                    ts[k][l][dir] = i;
                }
                pos = make_pair(k, l);
            } else {
                dir = (dir+1)%4;
                ts[pos.first][pos.second][dir] = i;
            }
        }
        while (rest >= 0) {
            const int k = pos.first + di[dir];
            const int l = pos.second + dj[dir];
            if (0 <= k && k < H && 0 <= l && l < W && grid[k][l] != '#') {
                pos = make_pair(k, l);
                --rest;
            } else {
                dir = (dir+1)%4;
            }
        }
        static const char tbl[] = "NESW";
        cout << pos.first+1 << ' ' << pos.second+1 << ' ' << tbl[dir] << endl;
    }
    return 0;
}
