//Name: Secret Milking Machine
//Level: 3
//Category: グラフ,Graph,最小費用流,Minimum Cost Flow
//Note:

/**
 * a + b = max(a, b)とした体の上で最小費用流。
 *
 * オーダーはO(TV log E)。
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

struct Edge {
    int from, to, len;
    int flow;
    Edge *back;

    Edge() {}
    Edge(int f, int t, int l) : from(f), to(t), len(l), flow(0) {}

    bool operator <(const Edge &e) const {
        return from < e.from;
    }
};

const int INF = 100000000;
int N;
Edge _edges[80001];
Edge *edges[80001];
Edge **start_of[200];

bool cmp(const Edge *a, const Edge *b) {
    return a->from < b->from;
}

int mincost_flow(int src, int sink, int flow) {
    static int cost[200];
    static Edge *prev[200];
    int ans = 0;
    while(flow > 0) {
        priority_queue<pair<int, int> > q;
        fill_n(cost, N, INF);
        q.push(make_pair(0, src));
        cost[0] = 0;
        while(!q.empty()) {
            const int cur_cost = -q.top().first;
            const int cur = q.top().second;
            q.pop();
            if(cur == sink) {
                break;
            }
            if(cur_cost > cost[cur]) continue;
            Edge **edge = start_of[cur];
            if(!edge) continue;
            for(; (*edge)->from == cur; ++edge) {
                if((*edge)->flow >= 1) continue;
                const int nc = max(cur_cost, (*edge)->len);
                if(cost[(*edge)->to] <= nc) continue;
                cost[(*edge)->to] = nc;
                prev[(*edge)->to] = *edge;
                q.push(make_pair(-nc, (*edge)->to));
            }
        }
        if(cost[sink] == INF) break;
        ans = max(ans, cost[sink]);
        int aug = flow;
        {
            int cur = sink;
            while(cur != src) {
                aug = min(aug, 1 - prev[cur]->flow);
                cur = prev[cur]->from;
            }
            cur = sink;
            while(cur != src) {
                prev[cur]->flow += aug;
                prev[cur]->back->flow -= aug;
                cur = prev[cur]->from;
            }
        }
        flow -= aug;
    }
    return ans;
}

bool solve() {
    int P, T;
    if(scanf("%d %d %d", &N, &P, &T) == EOF) return false;
    for(int i = 0; i < N; ++i) {
        start_of[i] = NULL;
    }
    for(int i = 0; i < P*2+1; ++i) {
        edges[i] = _edges + i;
    }
    for(int i = 0; i < P; ++i) {
        int a, b, l;
        scanf("%d %d %d", &a, &b, &l);
        --a; --b;
        *edges[i*2] = Edge(a, b, l);
        *edges[i*2+1] = Edge(b, a, l);
        edges[i*2]->back = edges[i*2+1];
        edges[i*2+1]->back = edges[i*2];
    }
    _edges[P*2+1].from = INF;
    sort(edges, edges+P*2, cmp);
    for(int i = 0; i < P*2; ++i) {
        if(i == 0) {
            start_of[edges[i]->from] = &edges[i];
        } else {
            if(edges[i]->from != edges[i-1]->from) start_of[edges[i]->from] = &edges[i];
        }
        //printf("%d %d %p\n", edges[i]->from, edges[i]->len);
    }
    printf("%d\n", mincost_flow(0, N-1, T));
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
