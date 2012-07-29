#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Tag {
    int r, c, dir;
    int cost;

    Tag() {}
    Tag(int r, int c, int dir, int cost) : r(r), c(c), dir(dir), cost(cost) {}

    bool operator <(const Tag &other) const {
        return cost > other.cost;
    }
};

// dir = EAST, NORTH, WEST, SOUTH
int DR[4] = {0, -1, 0, 1};
int DC[4] = {1, 0, -1, 0};
// {STRAIGHT, RIGHT, BACK, LEFT}
int DD[4] = {0, 3, 2, 1};

inline bool in_range(int a, int x, int b) {
    return a <= x && x < b;
}

bool update(int &a, int v) {
    if(v < a) {
        a = v;
        return true;
    }
    return false;
}

// memo[dir][r][c]
int memo[4][30][30];
int main() {
    while(true) {
        int W, H;
        cin >> W >> H;
        if(!W && !H) break;

        vector<vector<int> > field(H);
        for(int i = 0; i < H; ++i) {
            field[i].resize(W);
            for(int j = 0; j < W; ++j) {
                cin >> field[i][j];
            }
        }
        vector<int> cost(4);
        for(int i = 0; i < 4; ++i) {
            cin >> cost[i];
        }

        for(int dir = 0; dir < 4; ++dir) {
            for(int r = 0; r < H; ++r) {
                for(int c = 0; c < W; ++c) {
                    memo[dir][r][c] = INT_MAX;
                }
            }
        }
        int ans = -1;
        priority_queue<Tag> q;
        q.push(Tag(0, 0, 0, 0));
        memo[0][0][0] = 0;
        while(!q.empty()) {
            Tag cur = q.top();
            q.pop();
            if(cur.r == H-1 && cur.c == W-1) {
                ans = cur.cost;
                break;
            }
            if(memo[cur.dir][cur.r][cur.c] < cur.cost) continue;

            for(int act = 0; act < 4; ++act) {
                const int ncost = (field[cur.r][cur.c] == act) ? cur.cost : (cur.cost+cost[act]);
                const int nd = (cur.dir + DD[act]) % 4;
                const int nr = cur.r + DR[nd];
                const int nc = cur.c + DC[nd];
                if(in_range(0, nr, H) && in_range(0, nc, W)) {
                    if(update(memo[nd][nr][nc], ncost)) {
                        q.push(Tag(nr, nc, nd, ncost));
                    }
                }
            }
        }

        cout << ans << endl;
    }

    return 0;
}
