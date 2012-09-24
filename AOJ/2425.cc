//Name: A Holiday of Miss Brute Force
//Level: 2
//Category: 最短経路,ハニカム,Honeycomb,ダイクストラ,Dijkstra
//Note:

/*
 * ハニカムはX座標の偶奇でY座標の移動テーブルを変えれば対応できる．
 * あとは[X][Y][ターン数%6]の各状態に辿りつくまでに無視した最小回数を管理しつつダイクストラ．
 *
 * 頂点数 O(lx*ly) ，辺数 O(lx*ly) のダイクストラであることから，計算量は O(lx*ly log(lx*ly))
 */
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

struct Tag {
    int x, y, state;
    int cost;
    Tag(int x, int y, int s, int cost) : x(x), y(y), state(s), cost(cost) {}

    bool operator <(const Tag &other) const {
        return cost > other.cost;
    }
};

const int DX[7] = {0, 1, 1, 0, -1, -1, 0};
const int DY[2][7] = {
    {1, 0, -1, -1, -1, 0, 0}, //Even
    {1, 1, 0, -1, 0, 1, 0} //Odd
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int SX, SY, GX, GY;
    cin >> SX >> SY >> GX >> GY;
    int N;
    cin >> N;
    vector<vector<int> > movable(201, vector<int>(201, 1));
    vector<vector<vector<int> > > memo(201, vector<vector<int> >(201, vector<int>(6, INT_MAX)));
    for(int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        movable[y+100][x+100] = 0;
    }
    int LX, LY;
    cin >> LX >> LY;

    int ans = -1;
    priority_queue<Tag> q;
    q.push(Tag(SX, SY, 0, 0));
    while(!q.empty()) {
        Tag t = q.top();
        q.pop();
        if(t.x == GX && t.y == GY) {
            ans = t.cost;
            break;
        }
        if(memo[t.y+100][t.x+100][t.state] < t.cost) continue;
        memo[t.y+100][t.x+100][t.state] = t.cost;

        const int nocost = abs(t.x * t.y * t.state) % 6;
        for(int i = 0; i < 7; ++i) {
            const int nx = t.x + DX[i];
            const int ny = t.y + DY[t.x&1][i];
            const int nt = (t.state + 1) % 6;
            if(nx < -LX || nx > LX || ny < -LY || ny > LY) continue;
            if(!movable[ny+100][nx+100]) continue;
            int cost = t.cost + (i == nocost ? 0 : 1);
            if(memo[ny+100][nx+100][nt] > cost) {
                memo[ny+100][nx+100][nt] = cost;
                q.push(Tag(nx, ny, nt, cost));
            }
        }
    }
    cout << ans << endl;
    return 0;
}
