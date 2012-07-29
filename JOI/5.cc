#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <utility>
#include <cctype>

using namespace std;

const int dx[] = {0, -1, 0, 1};
const int dy[] = {-1, 0, 1, 0};

bool inRange(int a, int x, int b) {
    return a <= x && x <= b;
}

int main() {
    int H, W, N;
    cin >> H >> W >> N;

    vector<string> m;
    vector<pair<int,int> > targets(N); //Order: (H, W)

    int mr, mc;
    for(int i = 0; i < H; ++i) {
        string str;
        cin >> str;
        for(int j = 0; j < str.size(); ++j) {
            if(isdigit(str[j])) targets[str[j]-'0'-1] = make_pair(i, j);
            if(str[j] == 'S') {
                mr = i;
                mc = j;
            }
        }
        m.push_back(str);
    }

    int ans = 0;
    for(int T = 0; T < N; ++T) {
        int tr = targets[T].first;
        int tc = targets[T].second;
        vector<vector<bool> > visited(H, vector<bool>(W, false));

        queue<pair<int, pair<int, int> > > q;
        q.push(make_pair(0, make_pair(mr, mc)));
        while(!q.empty()) {
            int cost = q.front().first;
            int row = q.front().second.first;
            int col = q.front().second.second;

            q.pop();

            if(row == tr && col == tc) {
                ans += cost;
                mr = tr;
                mc = tc;
                break;
            }

            for(int i = 0; i < 4; ++i) {
                int nr = row + dy[i];
                int nc = col + dx[i];
                if(!inRange(0, nr, H-1) || !inRange(0, nc, W-1)) continue;
                if(m[nr][nc] == 'X') continue;
                if(visited[nr][nc]) continue;
                visited[nr][nc] = true;
                q.push(make_pair(cost+1, make_pair(nr, nc)));
            }
        }
    }
    cout << ans << endl;
    return 0;
}
