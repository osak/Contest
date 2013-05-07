//Name: Tree Reconstruction
//Level: 3
//Category: グラフ,Graph
//Note:

/*
 * 各連結成分について，(辺数)-(頂点数)+1を合計したものが答えとなる．
 * 直感的には，ひとつの頂点はコストの不明な辺が高々1本であれば再構成が可能であり，
 * ただし全ての頂点で1本ずつコストが不明だとこれらの辺を用いて無限にフローが流せるため，
 * どこか1箇所は決めなければならないとして考えられる．
 *
 * オーダーはO(M)．
 */
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

pair<int,int> dfs(int pos, const vector<vector<int> > &graph, vector<int> &visited) {
    const vector<int> &row = graph[pos];
    visited[pos] = 1;
    pair<int,int> res(1, row.size());
    for(vector<int>::const_iterator it = row.begin(); it != row.end(); ++it) {
        if(!visited[*it]) {
            pair<int,int> sub = dfs(*it, graph, visited);
            res.first += sub.first;
            res.second += sub.second;
        }
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N, M;
    cin >> N >> M;
    vector<vector<int> > graph(N);
    for(int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        graph[a].push_back(b);
    }

    vector<int> visited(N, 0);
    int ans = 0;
    for(int i = 0; i < N; ++i) {
        if(!visited[i]) {
            pair<int,int> res = dfs(i, graph, visited);
            ans += res.second - res.first + 1;
        }
    }
    cout << ans << endl;
    return 0;
}
