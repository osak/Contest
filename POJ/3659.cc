//Name: Cell Phone Network
//Level: 3
//Category: 動的計画法,DP,木DP
//Note:

/**
 * 木をたどりながら、「子がすべてカバーされていて、自分の状態が(被覆されていない, 被覆済み, 塔が立っている)の各状態であるときの最低本数」
 * について遷移を考え、DPする。
 *
 * オーダーはO(N)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

const int INF = 100000;

struct Edge {
    int from, to;
    Edge *next;
};
Edge _edges[20000];
int _pos;
Edge *graph[10000];

void add_edge(int from, int to) {
    Edge *e = &_edges[_pos++];
    e->from = from;
    e->to = to;
    e->next = graph[from];
    graph[from] = e;
}

enum State {
    UNCOVERED,
    COVERED,
    TOWERED
};

void add_undirectional_edge(int from, int to) {
    add_edge(from, to);
    add_edge(to, from);
}

void calc(int v, int parent, int *dp) {
    for(Edge *e = graph[v]; e; e = e->next) {
        if(e->to == parent) continue;
        int tmp[3] = {0, INF, INF};
        calc(e->to, v, tmp);
        const int nu = dp[UNCOVERED] + min(tmp[COVERED], tmp[TOWERED]);
        const int nc = min(dp[COVERED] + min(tmp[COVERED], tmp[TOWERED]),
                           dp[UNCOVERED] + tmp[TOWERED]);
        const int nt = min(dp[TOWERED] + *min_element(tmp, tmp+3),
                           min(dp[UNCOVERED] + *min_element(tmp, tmp+3)+1,
                               dp[COVERED] + *min_element(tmp, tmp+3)+1));
        dp[UNCOVERED] = nu;
        dp[COVERED] = nc;
        dp[TOWERED] = nt;
    }
}

bool solve() {
    int N;
    if(scanf("%d", &N) == EOF) return false;

    static int degree[10000];
    fill_n(degree, N, 0);
    fill_n(graph, N, (Edge*)NULL);
    _pos = 0;
    TIMES(i, N-1) {
        int a, b;
        scanf("%d %d", &a, &b);
        --a; --b;
        add_undirectional_edge(a, b);
        ++degree[a]; ++degree[b];
    }
    if(N == 1) {
        puts("1");
        return true;
    }

    int dp[3] = {0, INF, INF};
    calc(0, -1, dp);
    printf("%d\n", min(dp[COVERED], dp[TOWERED]));
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
