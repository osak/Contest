//Name: Merry Christmas
//Level: 4
//Category: グラフ,Graph,DAG,パス被覆,最大二部マッチング
//Note:

/**
 * それぞれのクエリに対して、同じサンタが処理できるかどうかは、都市間の距離とクエリの時間から判定できる。
 * この関係はDAGになり、問題は、最小のパス数でDAGの全ての頂点を被覆するという問題になる。
 * これは(頂点数 - 最大二部マッチングの個数)と等しい。
 * （ある頂点から次にどこに行くかという関係をマッチングで決めると、左側の頂点でマッチ先のないものがパスの終点になる。
 * すなわち終点の数だけパスが存在するが、最大二部マッチングはこれを最小化する。）
 *
 * オーダーは O(N^3 + NM)。
 */
#include <iostream>
#include <vector>
#include <valarray>
#include <queue>

using namespace std;

typedef long long LL;

bool bm_augment(const vector<vector<int>> &graph, int v, vector<int> &match_to, vector<bool> &visited) {
    if(v == -1) return true;
    if(visited[v]) return false;
    visited[v] = true;
    for(int n : graph[v]) {
        if(bm_augment(graph, match_to[n], match_to, visited)) {
            match_to[n] = v;
            return true;
        }
    }
    return false;
}

int bipartite_matching(const vector<vector<int>> &graph) {
    const int N = graph.size();
    vector<int> match_to(N, -1);
    int cnt = 0;
    for(int i = 0; i < N; ++i) {
        vector<bool> visited(N, false);
        if(bm_augment(graph, i, match_to, visited)) ++cnt;
    }
    return cnt;
}

bool solve() {
    int N, M, L;
    if(!(cin >> N >> M >> L)) return false;
    if(!N && !M && !L) return false;

    vector<vector<int>> dist(N, vector<int>(N, -1));
    for(int i = 0; i < M; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        dist[u][v] = dist[v][u] = d;
    }
    for(int i = 0; i < N; ++i) {
        dist[i][i] = 0;
    }
    for(int k = 0; k < N; ++k) {
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                if(dist[i][k] == -1 || dist[k][j] == -1) continue;
                const int d = dist[i][k] + dist[k][j];
                if(dist[i][j] == -1 || dist[i][j] > d) dist[i][j] = d;
            }
        }
    }

    vector<vector<int>> graph(L);
    vector<pair<LL,int>> queries(L);
    for(int i = 0; i < L; ++i) {
        cin >> queries[i].second >> queries[i].first;
    }
    sort(queries.begin(), queries.end());
    for(int i = 0; i < L; ++i) {
        const auto &qi = queries[i];
        for(int j = i+1; j < L; ++j) {
            const auto &qj = queries[j];
            if(dist[qi.second][qj.second] != -1 && qj.first - qi.first >= dist[qi.second][qj.second]) {
                graph[i].push_back(j);
            }
        }
    }
    int cnt = bipartite_matching(graph);
    cout << L-cnt << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
