//Name: System Engineer
//Level: 3
//Category: 二部マッチング
//Note: 高速化が必要

/*
 * 二部マッチングするだけ．
 * POJだとかなりTLEが厳しく，二部マッチングの引数をグローバル化しないと通らない．
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <cctype>
#include <cstring>
#include <cstdio>

using namespace std;

struct Edge {
    int from, to;
    Edge() {}
    Edge(int f, int t) : from(f), to(t) {}
    bool operator <(const Edge &other) const {
        return from < other.from;
    }
};

int match_to[20000];
bool visited[20000];
Edge edgelist[1000000];
int starts[10000];
bool bm_augment(int ES, int u) {
    if(u < 0) return true;
    //const int ES = edgelist.size();
    for(int i = starts[u]; i < ES && edgelist[i].from == u; ++i) {
        const int to = edgelist[i].to;
        if(!visited[to]) {
            visited[to] = true;
            if(bm_augment(ES, match_to[to])) {
                match_to[u] = to;
                match_to[to] = u;
                return true;
            }
        }
    }
    return false;
}

int bipartite_matching(int ES, int N, int L) {
    //const int N = g.size();
    //vector<int> match_to(N, -1);
    memset(match_to, -1, sizeof(match_to));
    int match = 0;
    for(int u = 0; u < L; ++u) {
        //vector<int> visited(N, false);
        memset(visited, 0, sizeof(visited));
        if(bm_augment(ES, u)) {
            ++match;
        }
    }
    return match;
}

int main() {
    //cin.tie(0);
    //ios::sync_with_stdio(0);
    int N;
    while(scanf(" %d ", &N) != EOF) {
        int edgeptr = 0;
        for(int k = 0; k < N; ++k) {
            int jobnr, servers;
            scanf(" %d : ( %d )", &jobnr, &servers);
            while(servers--) {
                int srv;
                scanf(" %d ", &srv);
                edgelist[edgeptr++] = Edge(jobnr, srv);
            }
        }
        sort(edgelist, edgelist+edgeptr);
        const int ES = edgeptr;
        for(int i = 0; i < N; ++i) {
            starts[i] = ES;
        }
        for(int i = 0; i < ES; ++i) {
            const int from = edgelist[i].from;
            //cout << edgelist[i].from << ' ' << edgelist[i].to << endl;
            starts[from] = min(starts[from], i);
        }
        /*
        for(int i = 0; i < N; ++i) {
            cout << starts[i] << endl;
        }
        */
        //cout << bipartite_matching(edgelist, ES, starts, 2*N, N) << endl;
        int ans = bipartite_matching(ES, 2*N, N);
        printf("%d\n", ans);
    }
    return 0;
}
