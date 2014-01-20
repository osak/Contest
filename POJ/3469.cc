//Name: Dual Core CPU
//Level: 5
//Category: グラフ,Graph,最小カット
//Note:

/**
 * それぞれのタスクを2つのグループに割り当てる問題で、コストの最小化なのでグラフの最小カットになる。
 * あるタスクをAに割り当てるかBに割り当てるかは、それぞれソースへの割り当て、シンクへの割り当てに対応し、
 * 逆側の辺にコストを割り当てる。
 * また、同じ割り当てにしないと追加コストが発生する組は、無向辺で互いを結ぶことで表現できる。
 * （頂点を2倍化したときは、同じ頂点を結ぶ辺を無向にするとよい）
 * あとは、このグラフ上で最大流を求めると、最小カット最大フロー定理により、これは最小カットとなる。
 *
 * オーダーはO(N^2 M)。
 * ただしDinicなので実際はオーダー以上に速いはずである。
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
#include <cstring>
#include <deque>
#include <cassert>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

typedef long long LL;

struct Edge {
    int from, to;
    LL cap, flow;
    Edge *back;
    Edge *next;
};
Edge _edges[800000 + 40000 + 40000 + 40000 + 10];
int _pos;
Edge* graph[40002+10];

void add_edge(int a, int b, LL cap) {
    Edge *ea = &_edges[_pos++];
    Edge *eb = &_edges[_pos++];
    ea->from = eb->to = a;
    eb->from = ea->to = b;
    ea->cap = cap;
    eb->cap = 0;
    ea->flow = eb->flow = 0;
    ea->back = eb;
    eb->back = ea;
    ea->next = graph[a];
    graph[a] = ea;
    eb->next = graph[b];
    graph[b] = eb;
}

const LL INF = 1LL << 50;
int level[40002+10];
bool finished[40002+10];

int SINK;
template <class T>
T dinic_augment(int u, T cur)
{
    if (u == SINK || cur == 0) {
        //printf("%lld\n", cur);
        return cur;
    }
    if (finished[u]) {
        return 0;
    }
    T sum = 0;
    finished[u] = true;
    for(Edge *e = graph[u]; e; e = e->next) {
        if(e->cap - e->flow > 0 && level[e->to] > level[u]) {
            const T aug = e->cap - e->flow;
            const T f = dinic_augment(e->to, min(cur - sum, aug));
            if(f > 0) {
                e->flow += f;
                e->back->flow -= f;
                finished[u] = false;
                sum += f;
                if(sum == cur) break;
            }
        }
    }
    return sum;
}/*}}}*/

// O(V^2 E)
template <typename T>
T dinic(int N, int source)/*{{{*/
{
    T max_flow = 0;

    while (true) {
        fill_n(level, 40002, -1);
        //memset(level, -1, sizeof(level));
        level[source] = 0;
        //static queue<int> q;
        queue<int> q;
        //q.clear();
        q.push(source);

        int d = N;
        while (!q.empty() && level[q.front()] < d) {
            const int u = q.front();
            q.pop();

            //for(list<Edge*>::const_iterator it = graph[u].begin(), eit = graph[u].end(); it != eit; ++it) {
            for(Edge *e = graph[u]; e; e = e->next) {
                if (level[e->to] < 0 && e->cap - e->flow > 0) {
                    q.push(e->to);
                    level[e->to] = level[u] + 1;
                }
            }
            if (u == SINK) {
                d = level[u];
                break;
            }
        }

        fill_n(finished, 40002, false);
        //memset(finished, 0, sizeof(finished));
        bool updated = false;
        while (true) {
            const T f = dinic_augment(source, INF);
            if (f == 0) {
                break;
            }
            max_flow += f;
            updated = true;
        }

        if (!updated) {
            break;
        }
    }

    return max_flow;
}/*}}}*/

bool solve() {
    int N, M;
    if(scanf("%d %d", &N, &M) == EOF) return false;
    _pos = 0;
    const int SRC = N*2;
    SINK = N*2+1;
    TIMES(i, N) {
        LL a, b;
        scanf("%lld %lld", &a, &b);
        add_edge(SRC, i, b);
        add_edge(i+N, SINK, a);
        add_edge(i, i+N, INF);
        add_edge(i+N, i, INF);
    }
    TIMES(i, M) {
        int a, b;
        LL w;
        scanf("%d %d %lld", &a, &b, &w);
        --a; --b;
        add_edge(a, b+N, w);
        add_edge(b, a+N, w);
    }
    LL ans = dinic<LL>(N*2+2, SRC);
    printf("%lld\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
