//Name: Chase
//Level:
//Category:
//Note:

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <cstdio>

using namespace std;

struct Road {
    int to, cost;
    Road() {}
    Road(int t, int c) : to(t), cost(c) {}
};

struct Tag {
    int town, agents;
    double prob;
    Tag() {}
    Tag(int t, int a, double p) : town(t), agents(a), prob(p) {}

    bool operator <(const Tag &other) const {
        return prob > other.prob; // Reverse order
    }
};

vector<vector<Road> > shortest_paths(const vector<vector<Road> > &graph) {
    const int N = graph.size();
    vector<int> memo(N, 10000*N);
    vector<int> prev(N, -1);
    priority_queue<pair<int,int> > q;
    q.push(make_pair(0, 0));
    while(!q.empty()) {
        const int cost = -q.top().first;
        const int pos = q.top().second;
        q.pop();
        if(memo[pos] < cost) continue;
        const vector<Road> &roads = graph[pos];
        for(vector<Road>::const_iterator it = roads.begin(); it != roads.end(); ++it) {
            const int nc = cost + it->cost;
            if(nc < memo[it->to]) {
                memo[it->to] = nc;
                prev[it->to] = pos;
                q.push(make_pair(-nc, it->to));
            }
        }
    }

    vector<vector<Road> > routes(N);
    for(int i = 1; i < N; ++i) {
        if(prev[i] == -1) continue;
        routes[prev[i]].push_back(Road(i, 0));
        cout << prev[i] << "->" << i << endl;
    }
    return routes;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;
        vector<vector<Road> > graph(N);
        for(int i = 0; i < M; ++i) {
            int from;
            Road r;
            cin >> from >> r.to >> r.cost;
            graph[from].push_back(r);
            swap(from, r.to);
            graph[from].push_back(r);
        }
        int P;
        cin >> P;
        vector<vector<double> > mat(N, vector<double>(P+1, 0));
        for(int i = 0; i < N; ++i) {
            for(int j = 1; j <= P; ++j) {
                cin >> mat[i][j];
            }
        }

        vector<vector<Road> > routes = shortest_paths(graph);
        // Probability coming to town N with agent P without captured
        vector<vector<double> > memo(N, vector<double>(P+1, 1.0));
        priority_queue<Tag> q;
        for(int i = 0; i <= P; ++i) {
            memo[0][i] = 1-mat[0][P-i];
            q.push(Tag(0, i, memo[0][i]));
        }
        while(!q.empty()) {
            const Tag t = q.top();
            q.pop();
            if(memo[t.town][t.agents] < t.prob) continue;
            cout << t.town << ' ' << t.agents << ' ' << t.prob << endl;
            const vector<Road> &roads = routes[t.town];
            for(vector<Road>::const_iterator it = roads.begin(); it != roads.end(); ++it) {
                for(int i = 0; i <= t.agents; ++i) {
                    const double np = t.prob * (1-mat[it->to][t.agents-i]) / roads.size();
                    if(np < memo[it->to][i]) {
                        memo[it->to][i] = np;
                        q.push(Tag(it->to, i, np));
                    }
                }
            }
        }
        double ans = 1.0;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j <= P; ++j) {
                ans = min(ans, memo[i][j]);
            }
        }
        printf("%.2f\n", (1.0-ans)*100);
    }
    return 0;
}
