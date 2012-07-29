//Name: Identically Colored Panels Connection
//Level: 3
//Category: 全探索,シミュレーション
//Note:

/*
 * 色の変え方は高々6^4通り(最後の1回は固定)なので，ループ回数は高々 H*W*6^4 ≦ 82944 回．
 * 全て試せばよい．
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int DR[] = {-1, 0, 1, 0};
const int DC[] = {0, -1, 0, 1};

int paint(vector<vector<int> > &field, vector<vector<int> > &visited, int r, int c, int color) {
    const int H = field.size();
    const int W = field[0].size();
    visited[r][c] = true;

    int cnt = 1;
    for(int i = 0; i < 4; ++i) {
        int nr = r + DR[i];
        int nc = c + DC[i];
        if(0 <= nr && nr < H && 0 <= nc && nc < W) {
            if(!visited[nr][nc] && field[nr][nc] == field[r][c]) cnt += paint(field, visited, nr, nc, color);
        }
    }
    field[r][c] = color;

    return cnt;
}

int main() {
    while(true) {
        int H, W, C;
        cin >> H >> W >> C;
        if(!H && !W && !C) break;

        vector<vector<int> > v(H, vector<int>(W));
        for(int i = 0; i < H; ++i) {
            for(int j = 0; j < W; ++j) {
                cin >> v[i][j];
            }
        }

        int ans = 0;
        int lim = 1;
        for(int i = 0; i < 4; ++i) lim *= 6;
        for(int pat = 0; pat <= lim; ++pat) {
            vector<vector<int> > field = v;

            int tmp = pat;
            for(int i = 0; i < 4; ++i) {
                int color = tmp%6 + 1;
                tmp /= 6;
                vector<vector<int> > visited(H, vector<int>(W, 0));
                paint(field, visited, 0, 0, color);
            }
            {
                vector<vector<int> > visited(H, vector<int>(W, 0));
                paint(field, visited, 0, 0, C);
            }
            {
                vector<vector<int> > visited(H, vector<int>(W, 0));
                ans = max(ans, paint(field, visited, 0, 0, 7));
            }
        }

        cout << ans << endl;
    }

    return 0;
}
