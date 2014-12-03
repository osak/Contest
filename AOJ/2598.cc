//Name: Website Tour
//Level: 4
//Category: グラフ,Graph,動的計画法,DP,強連結成分分解,個数制限付きナップサック問題
//Note:

/**
 * 以下のどちらかの条件を満たすとき、ある頂点の広告は好きなだけ見ることができる。
 * ・自己ループをもつ
 * ・この頂点を含む強連結成分内に他の頂点が存在する
 * したがって、強連結成分分解したグラフを1ノードずつたどりながら、個数制限付きナップサック問題を解いていけばよい。
 * 個数制限付きナップサック問題は、荷物の重さを2冪で分解することにより、O(N log W)で計算できる。
 *
 * オーダーは O(NT log T)。
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;

struct Node {
    int p, t, k;
};

void dfs1(int pos, const vector<vector<int>> &g, vector<bool> &visited, vector<int> &buf) {
    if(visited[pos]) return;
    visited[pos] = true;
    for(int to : g[pos]) dfs1(to, g, visited, buf);
    buf.push_back(pos);
}

void dfs2(int pos, const vector<vector<int>> &g, int label, vector<int> &buf) {
    if(buf[pos] != -1) return;
    buf[pos] = label;
    for(int to : g[pos]) dfs2(to, g, label, buf);
}

vector<int> scc(const vector<vector<int>> &g) {
    const int N = g.size();
    vector<vector<int>> rev(N);
    for(int i = 0; i < N; ++i) {
        for(int to : g[i]) {
            rev[to].push_back(i);
        }
    }
    vector<bool> visited(N, false);
    vector<int> ord;
    for(int i = 0; i < N; ++i) {
        dfs1(i, g, visited, ord);
    }
    reverse(begin(ord), end(ord));
    vector<int> label(N, -1);
    int l = 0;
    for(int pos : ord) {
        if(label[pos] == -1) dfs2(pos, rev, l++, label);
    }
    return label;
}

bool solve() {
    int N, M, T;
    if(!(cin >> N >> M >> T)) return false;
    if(!N && !M && !T) return false;

    vector<Node> nodes(N);
    for(int i = 0; i < N; ++i) {
        cin >> nodes[i].p >> nodes[i].t >> nodes[i].k;
    }
    vector<vector<int>> g(N);
    vector<bool> self_looped(N, false);
    for(int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        if(a == b) self_looped[a] = true;
    }

    vector<int> label = scc(g);
    const int L = *max_element(begin(label), end(label)) + 1;
    vector<vector<int>> nodes_of(L);
    for(int i = 0; i < N; ++i) {
        nodes_of[label[i]].push_back(i);
    }

    vector<vector<long long>> dp(L, vector<long long>(T+1, 0));
    vector<unordered_set<int>> prev_of(L);
    long long ans = 0;
    for(int cur = 0; cur < L; ++cur) {
        for(int t = 0; t <= T; ++t) {
            for(int prev : prev_of[cur]) {
                dp[cur][t] = max(dp[cur][t], dp[prev][t]);
            }
        }
        for(int t = 1; t <= T; ++t) {
            dp[cur][t] = max(dp[cur][t], dp[cur][t-1]);
        }

        if(nodes_of[cur].size() >= 2 || self_looped[nodes_of[cur][0]]) {
            // Can take any numbers of advertisement
            for(int n : nodes_of[cur]) {
                int rem = nodes[n].k;
                for(int ord = 1; rem > 0; ord *= 2) {
                    const int k = min(ord, rem);
                    rem -= k;
                    for(int t = T; t >= 0; --t) {
                        if(t-k*nodes[n].t >= 0) dp[cur][t] = max(dp[cur][t], dp[cur][t-k*nodes[n].t] + k * nodes[n].p);
                    }
                }
            }
        } else {
            // Can take only one advertisement
            for(int t = T; t >= 0; --t) {
                for(int n : nodes_of[cur]) {
                    if(t-nodes[n].t >= 0) dp[cur][t] = max(dp[cur][t], dp[cur][t-nodes[n].t] + nodes[n].p);
                }
            }
        }
        for(int n : nodes_of[cur]) {
            for(int to : g[n]) {
                prev_of[label[to]].insert(cur);
            }
        }
        ans = max(ans, *max_element(begin(dp[cur]), end(dp[cur]))); 
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) ;
    return 0;
}
