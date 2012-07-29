#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Tag {
    int pos, used, cost;

    Tag() {}
    Tag(int p, int u, int c) : pos(p), used(u), cost(c) {}

    bool operator < (const Tag &other) const {
        if(cost != other.cost) return cost > other.cost;
        return used > other.used;
    }
};


int main() {
    ios::sync_with_stdio(0);
    while(true) {
        int N, M, C;
        cin >> N >> M >> C;
        if(!N && !M && !C) break;

        vector<vector<pair<int,int> > > v(N);
        for(int i = 0; i < M; ++i) {
            int f, t, c;
            cin >> f >> t >> c;
            --f; --t;
            v[f].push_back(make_pair(t, c));
        }

        int ans = INT_MAX;
        vector<vector<int> > dp(N, vector<int>(N+1, INT_MAX));
        priority_queue<Tag> q;
        q.push(Tag(0, 0, 0));
        while(!q.empty()) {
            Tag t = q.top();
            q.pop();

            if(t.pos == N-1 && t.cost <= C) {
                ans = min(ans, t.used);
                continue;
            }
            if(dp[t.pos][t.used] <= t.cost) continue;
            dp[t.pos][t.used] = t.cost;

            for(int i = 0; i < v[t.pos].size(); ++i) {
                const pair<int,int> &p = v[t.pos][i];
                if(t.cost+p.second < dp[p.first][t.used]) {
                    q.push(Tag(p.first, t.used, t.cost+p.second));
                }
                if(t.used+1 <= N && t.cost < dp[p.first][t.used+1]) {
                    q.push(Tag(p.first, t.used+1, t.cost));
                }
            }
        }

        cout << ans << endl;
    }

    return 0;
}
