#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

#define FOREACH(it,v) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

struct Edge {
    long long cap, flow;
    long long cost;
    int to;

    Edge() : flow(0) {}
    Edge(long long c, long long co, int to) : cap(c), flow(0), cost(co), to(to) {}
};

long long solve() {
    long long E, R;
    int N;
    cin >> E >> R >> N;
    vector<vector<Edge> > graph(N+2);
    const int SOURCE = N;
    const int SINK = N+1;
    vector<int> refcnt(N+2, 0);
    for(int i = 0; i < N; ++i) {
        long long v;
        cin >> v;
        graph[i].push_back(Edge(E, -v, SINK));
        graph[SOURCE].push_back(Edge(R, 0, i));
        if(i+1 < N) graph[i].push_back(Edge(E-R, 0, i+1));
        refcnt[i] = 2;
    }
    graph[SOURCE].push_back(Edge(E-R, 0, 0));
    refcnt[SOURCE] = 0;
    refcnt[SINK] = N;

    long long f = E + R*(N-1);
    long long ans = 0;
    while(f > 0) {
        vector<pair<int,Edge*> > prev(N+2, make_pair(-1, (Edge*)NULL));
        queue<int> q;
        q.push(SOURCE);
        while(!q.empty()) {
            int cur = q.front();
            q.pop();
            FOREACH(it, graph[cur]) {
                if(it->cap - it->flow > 0) {
                    if(it->to == SINK) {
                        if(prev[SINK].first == -1 || it->cost < prev[SINK].second->cost) {
                            prev[it->to] = make_pair(cur, &*it);
                        }
                    } else if(prev[it->to].first == -1) {
                        prev[it->to] = make_pair(cur, &*it);
                        q.push(it->to);
                    }
                }
            }
        }
        if(prev[SINK].first == -1) break;
        long long residual = f;
        for(int pos = SINK; prev[pos].first != -1; pos = prev[pos].first) {
            residual = min(residual, prev[pos].second->cap - prev[pos].second->flow);
            //cout << pos << ' ' << residual << endl;
        }
        for(int pos = SINK; prev[pos].first != -1; pos = prev[pos].first) {
            prev[pos].second->flow += residual;
            ans += prev[pos].second->cost * residual;
        }
        //cout << residual << ' ' << ans << endl;
        f -= residual;
        if(residual == 0) break;
    }

    return -ans;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    for(int CASE = 1; CASE <= T; ++CASE) {
        long long ans = solve();
        cout << "Case #" << CASE << ": " << ans << endl;
    }
}
