#include <iostream>
#include <string>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> Point;

int main() {
    int H, W;
    cin >> H >> W;

    vector<string> v(H);
    for(int i = 0; i < H; ++i)
        cin >> v[i];

    int ans = 50*50*9;
    vector<vector<int> > dp(H, vector<int>(W, 50*50*9));
    priority_queue<pair<int, Point> > q;
    q.push(make_pair(0, Point(0, 0)));
    while(!q.empty()) {
        const int cost = -q.top().first;
        const Point pos = q.top().second;
        q.pop();

        if(dp[pos.first][pos.second] <= cost) continue;
        if(pos.first == H-1 && pos.second == W-1) {
            ans = cost;
            break;
        }
        dp[pos.first][pos.second] = cost;

        if(pos.first + 1 < H) {
            const Point next = Point(pos.first+1, pos.second);
            const int nc = v[next.first][next.second] - '0';
            if(dp[next.first][next.second] > cost+nc) q.push(make_pair(-cost-nc, next));
        }
        if(pos.second + 1 < W) {
            const Point next = Point(pos.first, pos.second+1);
            const int nc = v[next.first][next.second] - '0';
            if(dp[next.first][next.second] > cost+nc) q.push(make_pair(-cost-nc, next));
        }
    }

    cout << ans << endl;

    return 0;
}
