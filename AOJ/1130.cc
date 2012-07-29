#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int paint(vector<string> &field, int x, int y) {
    int cnt = 0;

    for(int i = 0; i < 4; ++i) {
        int xx = x + dx[i];
        int yy = y + dy[i];

        if(xx < 0 || field[0].size() <= xx || yy < 0 || field.size() <= yy) continue;

        if(field[yy][xx] == '.') {
            field[yy][xx] = '#';
            cnt += paint(field, xx, yy)+1;
        }
    }
    return cnt;
}

int main() {
    while(true) {
        int W, H;
        cin >> W >> H;

        if(!W && !H) break;

        int sx, sy;
        vector<string> field(H);
        for(int i = 0; i < H; ++i) {
            cin >> field[i];
            for(int x = 0; x < W; ++x) {
                if(field[i][x] == '@') {
                    sx = x;
                    sy = i;
                }
            }
        }

        cout << paint(field, sx, sy)+1 << endl;
    }
    return 0;
}

