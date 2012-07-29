#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int,int> Point;

int main() {
    int W, H, N;

    cin >> W >> H >> N;

    vector<vector<bool> > wallX(W+1, vector<bool>(H+1, false));
    vector<vector<bool> > wallY(W+1, vector<bool>(H+1, false));
    while(N--) {
        int sx, sy, dx, dy;
        cin >> sx >> sy >> dx >> dy;

        int startx = min(sx, dx);
        int starty = min(sy, dy);
        int endx = max(sx, dx);
        int endy = max(sy, dy);

        if(sx == dx) {
            for(int y = starty; y < endy; ++y) wallY[sx][y] = true;
        }
        else {
            for(int x = startx; x < endx; ++x) wallX[x][sy] = true;
        }
    }

    Point start, end;
    cin >> start.first >> start.second >> end.first >> end.second;

    vector<vector<pair<int, Point> > > v(W, vector<pair<int, Point> >(H, make_pair(INT_MAX, Point(0,0))));
    queue<Point> q;
    q.push(start);
    while(!q.empty()) {
        Point p = q.front();
        int cost = v[p.first][p.second].first;
        q.pop();

        if(p == end) break;

        const int dx[] = {1, -1, 0, 0};
        const int dy[] = {0, 0, 1, -1};
        for(int i = 0; i < 4; ++i) {
            int x = p.first + dx[i];
            int y = p.second + dy[i];
            if(x < 0 || W <= x || y < 0 || H <= y) continue;
            if(dx[i] != 0 && wallY[max(x, p.first)][y]) continue;
            if(dy[i] != 0 && wallX[x][max(y, p.second)]) continue;

            int c = cost + 1;
            if(v[x][y].first > c) {
                v[x][y].first = c;
                v[x][y].second = p;
                q.push(Point(x, y));
            }
        }
    }
    int org = v[end.first][end.second].first;

    vector<Point> path;
    Point p = end;
    while(p != start) {
        path.push_back(p);
        p = v[p.first][p.second].second;
    }

    int ans = 0;
    for(int i = 0; i < (int)path.size()-1; ++i) {
        int sxx = path[i].first;
        int syy = path[i].second;
        int dxx = path[i+1].first;
        int dyy = path[i+1].second;
        if(sxx == dxx) {
            wallX[sxx][max(syy, dyy)] = true;
        }
        else {
            wallY[max(sxx, dxx)][syy] = true;
        }
        vector<vector<pair<int, Point> > > v(W, vector<pair<int, Point> >(H, make_pair(INT_MAX, Point(0,0))));
        queue<Point> q;
        q.push(start);
        while(!q.empty()) {
            Point p = q.front();
            int cost = v[p.first][p.second].first;
            q.pop();

            if(p == end) break;

            const int dx[] = {1, -1, 0, 0};
            const int dy[] = {0, 0, 1, -1};
            for(int i = 0; i < 4; ++i) {
                int x = p.first + dx[i];
                int y = p.second + dy[i];
                if(x < 0 || W <= x || y < 0 || H <= y) continue;
                if(dx[i] != 0 && wallY[max(x, p.first)][y]) continue;
                if(dy[i] != 0 && wallX[x][max(y, p.second)]) continue;

                int c = cost + 1;
                if(v[x][y].first > c) {
                    v[x][y].first = c;
                    v[x][y].second = p;
                    q.push(Point(x, y));
                }
            }
        }
        if(v[end.first][end.second].first != INT_MAX) {
            ans = max(ans, v[end.first][end.second].first-org);
        }

        if(sxx == dxx) {
            wallX[sxx][max(syy, dyy)] = false;
        }
        else {
            wallY[max(sxx, dxx)][syy] = false;
        }
    }

    cout << ans << endl;
    return 0;
}

