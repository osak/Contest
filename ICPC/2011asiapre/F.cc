#include <iostream>
#include <vector>
#include <queue>
using namespace std;
static const int INF = 10000000;

int main()
{
    int H, W, N;
    while (cin >> H >> W >> N && H != 0) {
        string stk;
        cin >> stk;
        vector<string> grid(H);
        pair<int,int> start;
        for (int i = 0; i < H; i++) {
            cin >> grid[i];
            for (int j = 0; j < W; j++) {
                if (grid[i][j] == 'S') {
                    start = make_pair(i, j);
                    grid[i][j] = '.';
                }
            }
        }
        vector<vector<int> > dirs(N+1, vector<int>(4, INF));
        for (int i = N-1; i >= 0; i--) {
            dirs[i][0] = 0;
            if (stk[i] == 'L') {
                dirs[i][3] = 1;
                dirs[i][1] = min(INF, 1+dirs[i+1][2]);
                dirs[i][2] = min(INF, 1+dirs[i+1][3]);
            } else {
                dirs[i][1] = 1;
                dirs[i][2] = min(INF, 1+dirs[i+1][1]);
                dirs[i][3] = min(INF, 1+dirs[i+1][2]);
            }
        }

        vector<vector<vector<int> > > dist(H, vector<vector<int> >(W, vector<int>(4, INF)));
        queue<pair<pair<int,int>, int> > q;
        q.push(make_pair(start, 0));
        dist[start.first][start.second][0] = 0;
        while (!q.empty()) {
            const pair<int,int> pos = q.front().first;
            const int dir = q.front().second;
            q.pop();
            if (grid[pos.first][pos.second] == 'G') {
                cout << "Yes" << endl;
                goto NEXT;
            }

            static const int di[] = {-1, 0, 1, 0}, dj[] = {0, 1, 0, -1};
            const int k = pos.first + di[dir];
            const int l = pos.second + dj[dir];
            if (0 <= k && k < H && 0 <= l && l < W && grid[k][l] != '#') {
                if (dist[pos.first][pos.second][dir] < dist[k][l][dir]) {
                    dist[k][l][dir] = dist[pos.first][pos.second][dir];
                    q.push(make_pair(make_pair(k, l), dir));
                }
            }

            const int stackpos = dist[pos.first][pos.second][dir];
            if (stackpos < N) {
                for (int d = 1; d < 4; d++) {
                    int next = dirs[stackpos][d] + stackpos;
                    int next_dir = (dir + d)%4;
                    if (next <= N &&  next < dist[pos.first][pos.second][next_dir]) {
                        dist[pos.first][pos.second][next_dir] = next;
                        q.push(make_pair(pos, next_dir));
                    }
                }
            }
        }
        cout << "No" << endl;
NEXT:
        ;
    }
    return 0;
}
