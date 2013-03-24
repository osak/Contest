//Name: Girls and Boys
//Level: 3
//Category: グラフ,Graph,二部グラフ,最大独立点集合,二部マッチング
//Note:

/*
 * 問題文にさらっと書かれているが，"between one girl and one boy" なので
 * Romantically involved関係は二部グラフになる．
 * 二部グラフの最大独立点集合は頂点数から二部マッチングの個数を引くことで求められる．
 *
 * この問題に関しては，左側頂点の集合を求めるのが面倒なので，中国人がよくやっている
 * 頂点を2倍化した二部マッチングを使うと楽．
 * (全ての頂点を左と右に並べて二部マッチングすると，同じマッチングを2回数えることになるが
 *  コーディングがかなり楽になる)
 *
 * オーダーは O(N(N+E))．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define TIMES(__i,__n) for(int __i = 0; __i < __n; ++__i)

typedef vector<int> GraphRow;
typedef vector<GraphRow> Graph;

Graph graph;
int to[500];
bool visited[500];

bool dfs(int pos) {
    if(pos == -1) return true;
    FOREACH(it, graph[pos]) {
        if(visited[*it]) continue;
        visited[*it] = true;
        if(dfs(to[*it])) {
            //to[pos] = *it;
            to[*it] = pos;
            return true;
        }
    }
    return false;
}

int bipartite_matching() {
    const int N = graph.size();
    fill_n(to, N, -1);
    int cnt = 0;
    TIMES(i, N) {
        fill_n(visited, N, false);
        if(dfs(i)) ++cnt;
    }
    return cnt;
}

int main() {
    int N;
    while(scanf("%d", &N) != EOF) {
        graph.clear();
        graph.resize(N);
        TIMES(i, N) {
            int id, k;
            scanf("%d: (%d)", &id, &k);
            while(k--) {
                int rel;
                scanf(" %d", &rel);
                graph[id].push_back(rel);
                graph[rel].push_back(id);
            }
        }

        int match = bipartite_matching();
        printf("%d\n", N-match/2);
    }
    return 0;
}
