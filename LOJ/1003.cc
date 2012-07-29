#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct Dict {
    map<string,int> dict;
    int idx;

    Dict() : idx(0) {}

    int get(const string &name) {
        if(dict.count(name)) return dict[name];
        return dict[name] = idx++;
    }

    int count() const {
        return idx;
    }
};

bool dfs(int cur, const vector<vector<int> > &graph, vector<int> &visited, vector<int> &visited_loop) {
    const vector<int> &v = graph[cur];

    visited[cur] = 1;
    visited_loop[cur] = 1;
    for(int i = 0; i < v.size(); ++i) {
        int next = v[i];
        if(visited_loop[next]) return false;
        if(visited[next]) continue;

        if(!dfs(next, graph, visited, visited_loop)) return false;
    }
    visited_loop[cur] = 0;

    return true;
}

int main() {
    ios::sync_with_stdio(0);

    int T;
    cin >> T;

    for(int CASE = 1; CASE <= T; ++CASE) {
        int M;
        cin >> M;

        Dict dict;
        vector<vector<int> > graph;

        while(M--) {
            string a, b;
            cin >> a >> b;
            int ai = dict.get(a), bi = dict.get(b);
            int cnt = max(ai, bi);
            if(graph.size() <= cnt) graph.resize(cnt*2+1);
            graph[ai].push_back(bi);
        }

        bool valid = true;
        vector<int> visited(dict.count(), 0);
        vector<int> visited_loop(dict.count(), 0);
        for(int i = 0; i < dict.count(); ++i) {
            if(visited[i]) continue;
            valid = dfs(i, graph, visited, visited_loop);
            if(!valid) break;
        }

        cout << "Case " << CASE << ": " << (valid?"Yes":"No") << endl;
    }

    return 0;
}
