#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Road {
    int to, cost;
};

int main() {
    ios::sync_with_stdio(0);
    int N, M;
    cin >> N >> M;

    vector<vector<Road> > v(N);
    for(int i = 0; i < M; ++i) {
        int from;
        Road r;
        cin >> from >> r.to >> r.cost;
        r.to--;
        from--;
        v[from].push_back(r);
    }

    int ans = 0;
    for(int T = 1; T <= N; ++T) {
        priority_queue<pair<int, int> > q;
        vector<int> dp(N, INT_MAX);
        q.push(make_pair(0, T-1));
        int target = T % N;
        int pathcost = -1;
        while(!q.empty()) {
            int cost = -q.top().first;
            int pos = q.top().second;
            q.pop();

            if(pos == target) {
                pathcost = cost;
                break;
            }

            for(int i = 0; i < v[pos].size(); ++i) {
                int to = v[pos][i].to;
                int cs = cost + v[pos][i].cost;
                if(dp[to] <= cs) continue;
                q.push(make_pair(-cost-v[pos][i].cost, v[pos][i].to));
                dp[to] = cs;
            }
        }
        if(pathcost == -1) {
            ans = -1;
            break;
        }
        ans += pathcost;
    }
    cout << ans << endl;
    return 0;
}
