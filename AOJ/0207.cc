//Name: Block
//Level: 2
//Category: グラフ,Graph,シミュレーション
//Note:

/**
 * 盤面が小さいので、実際にブロックを置いた状態をシミュレーションして
 * その上でスタートからゴールまでが連結であるかを調べればよい。
 *
 * オーダーは O(WH)。
 */
#include <iostream>
#include <vector>

using namespace std;

const int dx[] = {0, -1, 0, 1};
const int dy[] = {-1, 0, 1, 0};

bool fill(vector<vector<int> > &v, int x, int y, int gx, int gy) {
    if(x == gx && y == gy) return true;

    int W = v.size();
    int H = v[0].size();
    int clr = v[x][y];
    v[x][y] = 0;

    for(int i = 0; i < 4; ++i) {
        int xx = x + dx[i];
        int yy = y + dy[i];

        if(0 <= xx && xx < W && 0 <= yy && yy < H) {
            if(v[xx][yy] == clr) {
                if(fill(v, xx, yy, gx, gy)) return true;
            }
        }
    }
    return false;
}

int main() {
    while(true) {
        int W, H;
        int sx, sy, gx, gy;
        int N;

        cin >> W >> H;
        if(!W && !H) break;
        cin >> sx >> sy >> gx >> gy >> N;
        --sx; --sy; --gx; --gy;

        vector<vector<int> > v(W, vector<int>(H, 0));
        for(int i = 0; i < N; ++i) {
            int c, d, x, y;
            cin >> c >> d >> x >> y;
            --x; --y;
            int w = d ? 2 : 4;
            int h = d ? 4 : 2;
            for(int dx = 0; dx < w; ++dx) 
                for(int dy = 0; dy < h; ++dy)
                    v[x+dx][y+dy] = c;
        }

        if(v[sx][sy] != 0 && fill(v, sx, sy, gx, gy)) cout << "OK" << endl;
        else cout << "NG" << endl;
    }
    return 0;
}
