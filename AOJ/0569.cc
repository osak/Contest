//Name: Illumination
//Level: 3
//Category: 探索,塗り潰し
//Note:

/*
 * 建物を軸にして考えると面倒なので，侵入可能なマスに隣接する建物を考える．
 * 侵入可能なマスは，一繋がりの白マスをたどっていくと盤面の外に出られるもの．
 * したがって，繋がっている白マスを塗り潰しながら建物と共有している辺の数を数え，
 * 塗り潰しの途中で外周に出たかどうかでこの辺の数が有効かどうかを決めればよい．
 */
#include <iostream>
#include <cassert>

using namespace std;

const int DR[6] = {0, -1, -1, 0, 1, 1};
const int DC[2][6] = {
    {-1, -1, 0, 1, 0, -1}, // Even
    {-1, 0, 1, 1, 1, 0}, // Odd
};

int W, H;
int field[102][102];
bool outside(int r, int c) {
    return r < 0 || H <= r || c < 0 || W <= c;
}
int paint_area(int r, int c, bool &valid) {
    field[r][c] = 2;
    int len = 0;
    for(int edge = 0; edge < 6; ++edge) {
        const int nr = r + DR[edge];
        const int nc = c + DC[r&1][edge];
        if(outside(nr, nc)) {
            valid = true;
        }
        else { // inside
            int obj = field[nr][nc];
            if(obj == 1) {
                ++len;
            }
            else if(obj == 0) {
                len += paint_area(nr, nc, valid);
            }
        }
    }
    return len;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> W >> H;
    for(int r = 1; r <= H; ++r) {
        for(int c = 1; c <= W; ++c) {
            cin >> field[r][c];
        }
    }
    W += 2;
    H += 2;
    /*
    for(int r = 0; r < H; ++r) {
        if(r % 2 == 1) cout << ' ';
        for(int c = 0; c < W; ++c) {
            cout << field[r][c] << ' ';
        }
        cout << endl;
    }
    */

    int ans = 0;
    for(int r = 0; r < H; ++r) {
        for(int c = 0; c < W; ++c) {
            if(field[r][c] == 0) {
                bool valid = false;
                int len = paint_area(r, c, valid);
                if(valid) ans += len;
                //cout << r << ' ' << c << endl;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
