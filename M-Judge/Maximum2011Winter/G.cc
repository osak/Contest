#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Tag {
    int x, y, z, c;

    Tag() {}
    Tag(int xx, int yy, int zz, int cc) : x(xx), y(yy), z(zz), c(cc){}

    bool operator < (const Tag &other) const {
        return c > other.c;
    }
};

const int delta[][2] = {{1,0},{0,1},{-1,0},{0,-1}};

inline bool inRange(int a, int x, int b) {
    return a <= x && x <= b;
}

int main() {
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<vector<string> > maze(M, vector<string>(N));
        for(int i = 0; i < M; ++i) {
            for(int j = 0; j < N; ++j) {
                cin >> maze[i][j];
            }
        }
        int sx, sy;
        for(sx = 0; sx < N; ++sx)
            for(sy = 0; sy < N; ++sy)
                if(maze[0][sy][sx] == 'S') goto a;
a:
        int ans = -1;
        priority_queue<Tag> q;
        q.push(Tag(sx, sy, 0, 0));
        for(int m = 0; m < M; ++m) {
            priority_queue<Tag> nq;
            while(!q.empty()) {
                Tag t = q.top();
                q.pop();

                char m = maze[t.z][t.y][t.x];
                if(m == '*') continue;
                if(m == 'G') {
                    ans = t.c;
                    goto end;
                }
                maze[t.z][t.y][t.x] = '*';

                for(int i = 0; i < 4; ++i) {
                    int nx = t.x + delta[i][0];
                    int ny = t.y + delta[i][1];
                    if(inRange(0, nx, N-1) && inRange(0, ny, N-1)) {
                        if(maze[t.z][ny][nx] != '*') {
                            q.push(Tag(nx, ny, t.z, t.c+1));
                        }
                    }
                }
                if(m == 'U') {
                    int nx = t.x;
                    int ny = t.y;
                    for(int i = 0; i < 4; ++i) {
                        if(t.z+1 < M && maze[t.z+1][ny][nx] != '*' && maze[t.z+1][ny][nx] != 'U') {
                            nq.push(Tag(nx, ny, t.z+1, t.c+1));
                        }
                        int tmp = nx;
                        nx = ny;
                        ny = N-tmp-1;
                    }
                }
            }
            q = nq;
        }
end:
        cout << ans << endl;
    }
    return 0;
}
