//Name: Wormholes
//Level: 2
//Category: グラフ,Graph,負閉路,Bellman-Ford
//Note:

/**
 * スタート地点はどこでも良いので、負閉路があるかさえ判定できればよい。
 * これはBellman-FordでN+1回目のrelaxで変化が起きるかどうかで判定できる。
 *
 * オーダーはO(NM)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

typedef long long LL;
const LL INF = 10000LL * 2500;

struct Edge {
    int from, to;
    LL cost;
};

bool relax(const Edge *edges, const int N, const int M, LL *cost) {
    bool changed = false;
    TIMES(i, M) {
        const LL nc = cost[edges[i].from] + edges[i].cost;
        if(cost[edges[i].to] > nc) {
            cost[edges[i].to] = nc;
            changed = true;
        }
    }
    return changed;
}

bool solve() {
    int N, M, W;
    scanf("%d %d %d", &N, &M, &W);
    if(!N && !M && !W) return false;

    static Edge edges[5000+200];
    TIMES(i, M) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        --a; --b;
        edges[i*2] = Edge{a, b, c};
        edges[i*2+1] = Edge{b, a, c};
    }
    TIMES(i, W) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        --a; --b;
        edges[M*2+i] = Edge{a, b, -c};
    }
    static LL cost[500];
    fill_n(cost, 500, INF);
    cost[0] = 0;
    TIMES(i, N) {
        relax(edges, N, M*2+W, cost);
    }
    bool ok = relax(edges, N, M*2+W, cost);
    puts(ok ? "YES" : "NO");
    return true;
}

int main() {
    int F;
    scanf("%d", &F);
    while(F-- && solve()) ;
    return 0;
}
