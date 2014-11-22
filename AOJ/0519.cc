//Name: Worst Sportswriter
//Level: 3
//Category: グラフ,Graph,トポロジカルソート
//Note:

/**
 * 条件1〜3より、チーム間には全順序関係があることが分かる。
 * したがって、勝敗関係で有向グラフを作り、トポロジカルソートすると有効な順序がひとつ得られる。
 * これ以外の順序が存在するためには、元のグラフが1本の鎖になっていない（分枝をもつか、連結でない）必要がある。
 * また、この性質を満たすとき、順序の定義されない2ノードの順序は任意に決定できるため、複数の順序が存在する。
 *
 * オーダーは O(N + M)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

bool check(const vector<int> &ord, const vector<vector<int>> &g) {
    const int N = ord.size();
    for(int i = 0; i < N-1; ++i) {
        const int next = ord[i+1];
        if(find(begin(g[ord[i]]), end(g[ord[i]]), next) == end(g[ord[i]])) return false;
    }
    return true;
}

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    int M;
    cin >> M;
    vector<vector<int>> graph(N);
    for(int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a-1].push_back(b-1);
    }
    vector<int> ord = topological_sort(graph);
    const bool full_ordered = check(ord, graph);
    for(int o : ord) {
        cout << o+1 << endl;
    }
    cout << !full_ordered << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
