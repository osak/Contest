//Name: Telephone Lines
//Level: 3
//Category: グラフ,Graph,最短経路
//Note: lengthsはsegmentsと同義

/**
 * 1からNまでの経路を取って、長い方からK+1本目のコストを最小にする問題。
 * K本まで無効化できるので、[頂点数][あと何本無効化できるか]を状態として、それまでに使った最長辺をコストとした最短経路問題になる。
 *
 * オーダーはO(P log N)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <list>
#include <queue>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

struct Edge {
    int a, b, l;

    Edge() {}
    Edge(int a, int b, int l) : a(a), b(b), l(l) {}
};

list<Edge> graph[1000];

bool solve() {
    int N, P, K;
    if(scanf("%d %d %d", &N, &P, &K) == EOF) return false;

    TIMES(i, P) {
        int a, b, l;
        scanf("%d %d %d", &a, &b, &l);
        --a; --b;
        graph[a].push_back(Edge(a, b, l));
        graph[b].push_back(Edge(b, a, l));
    }
    static int memo[1000][1001];
    const int INF = 20000000;
    fill_n((int*)memo, 1000*1001, INF);
    priority_queue<pair<int, pair<int,int> > > q; // (-cost, (-rem, pos))
    q.push(make_pair(0, make_pair(-K, 0)));
    memo[0][K] = 0;
    while(!q.empty()) {
        const int cost = -q.top().first;
        const int rem = -q.top().second.first;
        const int pos = q.top().second.second;
        q.pop();
        if(memo[pos][rem] < cost) continue;
        if(pos == N-1) break;
        //printf("%d %d %d\n", cost, rem, pos+1);
        for(list<Edge>::const_iterator it = graph[pos].begin(); it != graph[pos].end(); ++it) {
            // free
            if(rem > 0) {
                const int nc = cost;
                const int nr = rem - 1;
                const int np = it->b;
                if(memo[np][nr] > nc) {
                    memo[np][nr] = nc;
                    q.push(make_pair(-nc, make_pair(-nr, np)));
                }
            }
            // non-free
            {
                const int nc = max(cost, it->l);
                const int nr = rem;
                const int np = it->b;
                if(memo[np][nr] > nc) {
                    memo[np][nr] = nc;
                    q.push(make_pair(-nc, make_pair(-nr, np)));
                }
            }
        }
    }
    int ans = *min_element(memo[N-1], memo[N]);
    if(ans == INF) ans = -1;
    printf("%d\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
