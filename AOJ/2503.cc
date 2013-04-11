//Name: Project Management
//Level: 2
//Category: グラフ,Graph,DAG,最長経路
//Note:

/*
 * 辺数が少ないので、コストの符号を反転してBellman-Fordすればよい。
 *
 * オーダーはO(NM)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define TIMES(i,n) for(int i = 0; i < (n); ++i)

struct Edge {
    int from, to;
    int cost;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, M;
    while(cin >> N >> M) {
        vector<Edge> edges(M);
        TIMES(i, M) {
            Edge &edge = edges[i];
            cin >> edge.from >> edge.to >> edge.cost;
        }
        vector<int> dist(N, 0);
        TIMES(_, N) {
            FOREACH(it, edges) {
                const Edge &edge = *it;
                dist[edge.to] = max(dist[edge.to], dist[edge.from] + edge.cost);
            }
        }
        cout << *max_element(dist.begin(), dist.end()) << endl;
    }
    return 0;
}
