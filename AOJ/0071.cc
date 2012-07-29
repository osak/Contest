//Name: Bombs Chain
//Level: 2
//Category: シミュレーション
//Note:

/*
 * 爆弾の爆発を愚直にシミュレートすればよい．
 */
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    for(int CASE = 1; CASE <= N; ++CASE) {
        vector<string> field(8);
        for(int i = 0; i < 8; ++i) cin >> field[i];
        int sx, sy;
        cin >> sx >> sy;
        sx--; sy--;

        queue<pair<int,int> > q;
        q.push(make_pair(sx, sy));
        field[sy][sx] = '0';
        while(!q.empty()) {
            int x = q.front().first, y = q.front().second;
            q.pop();

            for(int xx = max(0, x-3); xx <= min(7, x+3); ++xx) {
                if(field[y][xx] == '1') q.push(make_pair(xx, y));
                field[y][xx] = '0';
            }
            for(int yy = max(0, y-3); yy <= min(7, y+3); ++yy) {
                if(field[yy][x] == '1') q.push(make_pair(x, yy));
                field[yy][x] = '0';
            }
        }
        cout << "Data " << CASE << ":" << endl;
        for(int i = 0; i < 8; ++i) cout << field[i] << endl;
    }
    return 0;
}
