//Name: Taxis
//Level: 3
//Category: グラフ,Graph,最短経路
//Note:

/*
 * 各頂点から、距離R_i以内の頂点を幅優先探索で求めて、辺を張り直す。
 * このグラフの上で最短経路を求める。
 *
 * オーダーは O(N^2 log N)。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Tag {
    int c, r;
};

struct Edge {
    int to, c;
};

bool solve() {
    int N, K;
    if(!(cin >> N >> K)) return false;

    vector<vector<int>> org_g(N);
    vector<Tag> taxis(N);
    for(int i = 0; i < N; ++i) {
        cin >> taxis[i].c >> taxis[i].r;
    }
    for(int i = 0; i < K; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        org_g[a].push_back(b);
        org_g[b].push_back(a);
    }

    vector<vector<Edge>> g(N);
    for(int from = 0; from < N; ++from) {
        vector<int> q[2];
        vector<bool> visited(N, false);
        visited[from] = true;
        q[0].push_back(from);
        for(int i = 0; i < taxis[from].r; ++i) {
            q[1].clear();
            for(int v : q[0]) {
                for(int to : org_g[v]) {
                    if(!visited[to]) {
                        visited[to] = true;
                        q[1].push_back(to);
                        g[from].push_back(Edge{to, taxis[from].c});
                    }
                }
            }
            q[0].swap(q[1]);
        }
    }

    vector<int> memo(N, -1);
    priority_queue<pair<int,int>> q;
    q.push(make_pair(0, 0));
    memo[0] = 0;
    int ans = -1;
    while(!q.empty()) {
        const int cost = -q.top().first;
        const int v = q.top().second;
        q.pop();
        if(memo[v] < cost) continue;
        if(v == N-1) {
            ans = cost;
            break;
        }
        for(const Edge &e : g[v]) {
            const int nc = cost + e.c;
            if(memo[e.to] == -1 || memo[e.to] > nc) {
                memo[e.to] = nc;
                q.push(make_pair(-nc, e.to));
            }
        }
    }
    cout << ans << endl;
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
