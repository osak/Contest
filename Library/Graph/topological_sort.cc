// Topological sort using DFS.
// Runs in O(N + M)
void topological_inner(const vector<vector<int>> &g, int v, vector<int> &res, vector<bool> &visited) {
    visited[v] = true;
    for(int to : g[v]) {
        if(!visited[to]) {
            topological_inner(g, to, res, visited);
        }
    }
    res.push_back(v);
}

vector<int> topological_sort(const vector<vector<int>> &g) {
    const int N = g.size();
    vector<int> res;
    vector<bool> visited(N, false);
    for(int i = 0; i < N; ++i) {
        if(!visited[i]) {
            topological_inner(g, i, res, visited);
        }
    }
    reverse(begin(res), end(res));
    return res;
}

// Used in:
// AOJ0119
