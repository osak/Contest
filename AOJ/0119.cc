//Name: Taro's Obsession
//Level: 3
//Category: グラフ,Graph,DAG,トポロジカルソート
//Note: 

/**
 * 証言に矛盾がないことから、証言からできるグラフは必ずDAGとなる。
 * したがって、トポロジカルソートしたものは部屋に入った順番として有効なものになる。
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

bool solve() {
    int M, N;
    if(!(cin >> M >> N)) return false;
    vector<vector<int>> g(M);
    for(int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        g[x].push_back(y);
    }
    auto ord = topological_sort(g);
    for (auto i : ord) {
        cout << i+1 << endl;
    }
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
