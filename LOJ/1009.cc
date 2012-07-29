#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

ostream& ansout(int c) {
    return cout << "Case " << c << ": ";
}

void dfs(const vector<vector<int> > &graph, vector<int> &visited, int pos, int phase, int &c1, int &c2) {
    if(phase == 0) ++c1;
    else ++c2;
    visited[pos] = 1;

    const vector<int> &v = graph[pos];
    for(int i = 0; i < v.size(); ++i) {
        if(visited[v[i]]) continue;
        dfs(graph, visited, v[i], 1-phase, c1, c2);
    }
}

int main() {
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    for(int CASE = 1; CASE <= T; ++CASE) {
        int N;
        cin >> N;

        vector<vector<int> > graph;
        while(N--) {
            int u, v;
            cin >> u >> v;
            int maxval = max(u, v);
            if(maxval >= graph.size()) graph.resize(maxval+1);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        int ans = 0;
        vector<int> visited(graph.size(), 0);
        for(int i = 0; i < graph.size(); ++i) {
            if(visited[i]) continue;
            if(graph[i].size() == 0) continue;

            int c1 = 0, c2 = 0;
            dfs(graph, visited, i, 0, c1, c2);
            ans += max(c1, c2);
        }

        ansout(CASE) << ans << endl;
    }

    return 0;
}
