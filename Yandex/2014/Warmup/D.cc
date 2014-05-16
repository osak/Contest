#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef long long LL;
const LL INF = 1000LL * 1000;

bool solve() {
    int N, M;
    if(!(cin >> N >> M)) return false;
    if(!N && !M) return false;

    vector<vector<pair<int,int>>> graph(N);
    for(int i = 0; i < M; ++i) {
        int a, b, d;
        cin >> a >> b >> d;
        --a; --b;
        graph[a].push_back(make_pair(b, d));
        graph[b].push_back(make_pair(a, d));
    }

    vector<pair<int,LL>> memo(N, make_pair(0, INF));
    priority_queue<pair<LL,int>> q;
    q.push(make_pair(0, 0));
    while(!q.empty()) {
        const LL cost = -q.top().first;
        const int v = q.top().second;
        q.pop();
        if(cost > memo[v].second) continue;
        for(const auto &e : graph[v]) {
            const int next = e.first;
            const LL nc = cost + e.second;
            const int ne = memo[v].first + 1;
            if((nc < memo[next].second) || (nc == memo[next].second && ne > memo[next].first)) {
                memo[next] = make_pair(ne, nc);
                q.push(make_pair(-nc, next));
            }
        }
    }
    cout << memo[N-1].second << ' ' << memo[N-1].first << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
