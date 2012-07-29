#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>
#include <algorithm>

using namespace std;

struct Tag {
    int x, y, level;
    Tag() {}
    Tag(int xx, int yy, int l) : x(xx), y(yy), level(l) {}
};

bool operator < (const Tag &t1, const Tag &t2) {
    return t1.level > t2.level;
}

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void check(vector<vector<int> > &room, vector<pair<int, int> > &v, int sx, int sy) {
    int W = room[0].size();
    int H = room.size();

    priority_queue<Tag> q;
    q.push(Tag(sx, sy, room[sy][sx]));
    room[sy][sx] = 0;
    int level = 0;
    int cnt = 0;

    while(!q.empty()) {
        int x = q.top().x;
        int y = q.top().y;
        int lv = q.top().level;
        q.pop();

        if(lv > level) {
            v.push_back(make_pair(level, cnt));
            level = lv;
        }
        ++cnt;

        for(int i = 0; i < 4; ++i) {
            int nx = x+dx[i];
            int ny = y+dy[i];
            if(nx < 0 || W <= nx || ny < 0 || H <= ny) continue;
            if(room[ny][nx] == 0) continue;
            q.push(Tag(nx, ny, room[ny][nx]));
            room[ny][nx] = 0;
        }
    }
    v.push_back(make_pair(level, cnt));
}

int main() {
    while(true) {
        int R;
        cin >> R;
        if(!R) break;

        vector<pair<int, int> > v[2];
        for(int K = 0; K < 2; ++K) {
            int W, H, X, Y;
            cin >> W >> H >> X >> Y;
            vector<vector<int> > room(H, vector<int>(W));
            for(int i = 0; i < H; ++i) {
                for(int j = 0; j < W; ++j) {
                    cin >> room[i][j];
                }
            }
            check(room, v[K], X-1, Y-1);
        }

        int ans = INT_MAX;
        for(int i = 0; i < v[0].size(); ++i) {
            int l = v[0][i].first;
            int rem = R-v[0][i].second;
            //cout << l << ':' << rem << endl;
            if(rem <= 0) {
                ans = min(ans, l);
                break;
            }

            int left = 0, right = v[1].size();
            while(left < right) {
                int center = (left+right)/2;
                int cr = v[1][center].second;
                if(cr < rem) left = center+1;
                else right = center;
            }
            if(left >= v[1].size()) continue;
            ans = min(ans, l+v[1][left].first);
        }
        cout << ans << endl;
    }
    return 0;
}
