#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

/*
int maxflow(const vector<vector<pair<int, int> >  > &flow_v, int s, int g) {
    const int size = flow_v.size();

    vector<vector<int> > capacity(size, vector<int>(size, 0));
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < flow_v[i].size(); ++j) {
            int to = flow_v[i][j].first;
            int cost = flow_v[i][j].second;
            capacity[i][to] = cost;
        }
    }
    vector<vector<int> > flow(size, vector<int>(size, 0));

    int ans = 0;
    while(true) {
        queue<int> q;
        vector<int> prev(size, -1);
        prev[s] = s;
        q.push(s);
        while(!q.empty()) {
            int n = q.front();
            q.pop();
            for(int i = 0; i < size; ++i) {
                if(capacity[n][i] - flow[n][i] <= 0) continue;
                if(prev[i] != -1) continue;
                prev[i] = n;
                q.push(i);
                if(i == g) goto endloop;
            }
        }
endloop:
        if(prev[g] == -1) break;
        int res = INT_MAX;
        for(int i = g; prev[i] != i; i = prev[i]) {
            res = min(res, capacity[prev[i]][i]-flow[prev[i]][i]);
        }
        for(int i = g; prev[i] != i; i = prev[i]) {
            flow[orev[i]][i] += res;
            flow[i][prev[i]] -= res;
        }
        ans += res;
    }
    return ans;
}
*/

int main() {
    ios::sync_with_stdio(0);
    int N, M;
    cin >> N >> M;

    vector<vector<int> > v(N+1, vector<int>(N+1, 0));
    vector<vector<int> > d(N+1, vector<int>(N+1, 0));
    vector<vector<int> > num(N+1, vector<int>(N+1, 0));
    for(int i = 0; i < M; ++i) {
        int x, y;
        cin >> x >> y;
        v[x][y] = v[y][x] = 1;
        d[x][y] = 1;
        num[x][y] = num[y][x] = i+1;
    }

    int S, G;
    cin >> S >> G;

    int ans = 0;
    vector<int> flips;
    while(true) {
        bool modified = false;

        queue<int> q;
        vector<int> prev(N+1, -1);
        prev[S] = 0;
        q.push(S);
        while(!q.empty()) {
            int p = q.front();
            q.pop();

            if(p == G) {
                ++ans;
                int cur = p;
                while(cur != S) {
                    if(!d[prev[cur]][cur]) {
                        flips.push_back(num[prev[cur]][cur]);
                    }
                    v[cur][prev[cur]] = v[prev[cur]][cur] = 0;
                    cur = prev[cur];
                }
                modified = true;
                break;
            }

            for(int i = 0; i < N+1; ++i) {
                if(v[p][i] && prev[i] == -1) {
                    prev[i] = p;
                    q.push(i);
                }
            }
        }
        if(!modified) break;
    }

    cout << ans << endl;
    cout << flips.size() << endl;;
    for(int i = 0; i < flips.size(); ++i) {
        cout << flips[i] << endl;
    }

    return 0;
}
