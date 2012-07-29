#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

struct Tag {
    int x, y;
    int cost;
    Tag() {}
    Tag(int x, int y, int c) : x(x), y(y), cost(c) {}
};

inline bool inRange(int a, int x, int b) {
    return a <= x && x < b;
}

int main() {
    while(true) {
        int W, H;
        cin >> W >> H;
        if(!W && !H) break;

        int v[W*2][H*2];
        memset(v, 0, sizeof(v));
        for(int i = 0; i < H*2-1; ++i) {
            if(i % 2 == 0) { //縦壁
                for(int j = 0; j < W-1; ++j) {
                    int w;
                    cin >> w;
                    v[j*2+1][(i/2)*2] = w;
                }
            }
            else {
                for(int j = 0; j < W; ++j) {
                    int w;
                    cin >> w;
                    v[j*2][(i/2)*2+1] = w;
                }
            }
        }

        for(int y = 0; y < H*2; ++y) v[W*2-1][y] = 1;
        for(int x = 0; x < W*2; ++x) v[x][H*2-1] = 1;
        /*
        for(int y = 0; y < H*2; ++y) {
            for(int x = 0; x < W*2; ++x) {
                cout << v[x][y] << ' ';
            }
            cout << endl;
        }
        */

        int ans = 0;
        int visited[W*2][H*2];
        int dt[][2] = {{0, -2}, {2, 0}, {0, 2}, {-2, 0}};
        memset(visited, 0, sizeof(visited));
        queue<Tag> q;
        q.push(Tag(0, 0, 0));
        while(!q.empty()) {
            const Tag t = q.front();
            q.pop();

            if(t.x == W*2-2 && t.y == H*2-2) {
                ans = t.cost+1;
                break;
            }

            for(int i = 0; i < 4; ++i) {
                int nx = t.x + dt[i][0];
                int ny = t.y + dt[i][1];
                int jx = t.x + dt[i][0]/2;
                int jy = t.y + dt[i][1]/2;
                if(inRange(0, nx, W*2) && inRange(0, ny, H*2) && 
                        !visited[nx][ny] && !v[jx][jy]) {
                    q.push(Tag(nx, ny, t.cost+1));
                    visited[nx][ny] = 1;
                }
            }
        }

        cout << ans << endl;
    }
    return 0;
}
