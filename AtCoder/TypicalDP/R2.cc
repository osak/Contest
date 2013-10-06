//Name: グラフ
//Level: 3
//Category: グラフ,Graph,動的計画法,DP,強連結成分分解
//Note:

/*
 * 同じ頂点を複数回通ってもいいので、強連結成分は縮約して、DAG上で考えることができる。
 * すべての頂点に接続するSuper Sourceを始点として、パスの端点を表すカーソルを動かしていくことを考えると
 * ある状態[c1][c2]から遷移可能な状態は
 * ・辺c1->i, c2->iが存在するとき、[i][i]に遷移可能
 * ・辺c1->iが存在するとき、[i][c2]に遷移可能
 * ・辺c2->iが存在するとき、[c1][i]に遷移可能
 * これをトポロジカル順序で処理していくことにより、DPに落とすことができる。
 *
 * オーダーは O(N^3)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs1(int pos, const vector<vector<int>> &graph, vector<int> &ord, vector<bool> &visited) {
    if(visited[pos]) return;
    visited[pos] = true;
    for(int neigh : graph[pos]) dfs1(neigh, graph, ord, visited);
    ord.push_back(pos);
}

void dfs2(int pos, int l, const vector<vector<int>> &graph, vector<int> &label, vector<bool> &visited) {
    if(visited[pos]) return;
    visited[pos] = true;
    label[pos] = l;
    for(int neigh : graph[pos]) {
        dfs2(neigh, l, graph, label, visited);
    }
}

// Returns (scc_label, scc_size)
pair<vector<int>,int> scc(const vector<vector<int>> &graph) {
    const int N = graph.size();
    vector<vector<int>> rev(N);
    for(int i = 0; i < N; ++i) {
        for(int j : graph[i]) {
            rev[j].push_back(i);
        }
    }
    vector<int> ord;
    vector<bool> visited(N, false);
    for(int i = 0; i < N; ++i) {
        if(!visited[i]) dfs1(i, graph, ord, visited);
    }
    reverse(ord.begin(), ord.end());
    fill(visited.begin(), visited.end(), false);
    vector<int> label(N);
    int l = 0;
    for(int pos : ord) {
        if(!visited[pos]) dfs2(pos, l++, rev, label, visited);
    }
    return make_pair(label, l);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    vector<vector<int>> graph(N+1);
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            int v;
            cin >> v;
            if(v) graph[i].push_back(j);
        }
        graph[N].push_back(i);
    }
    const auto scc_spec = scc(graph);
    const int M = scc_spec.second;

    vector<vector<bool>> adj(M, vector<bool>(M, false));
    for(int i = 0; i < N+1; ++i) {
        const int scc_i = scc_spec.first[i];
        for(int j : graph[i]) {
            const int scc_j = scc_spec.first[j];
            if(scc_i != scc_j) adj[scc_i][scc_j] = true;
        }
    }
    vector<int> val(M, 0);
    for(int l : scc_spec.first) {
        val[l]++;
    }

    // dp[cursor1][cursor2]
    // dp[i][j] == dp[j][i]
    vector<vector<int>> dp(M, vector<int>(M, 0));
    for(int i = 0; i < M; ++i) {
        for(int a = 0; a < i; ++a) {
            for(int b = 0; b < i; ++b) {
                if(adj[a][i] && adj[b][i]) dp[i][i] = max(dp[i][i], dp[a][b] + val[i]);
                if(adj[a][i]) dp[i][b] = dp[b][i] = max(dp[i][b], dp[a][b] + val[i]);
                if(adj[b][i]) dp[i][a] = dp[a][i] = max(dp[i][a], dp[a][b] + val[i]);
            }
        }
    }
    int ans = 0;
    for(auto &row : dp) {
        for(int v : row) {
            ans = max(ans, v);
        }
    }
    cout << ans << endl;
    return 0;
}
