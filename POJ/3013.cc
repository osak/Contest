//Name: Big Christmas Tree
//Level: 3
//Category: グラフ,Graph,最短経路
//Note:

/**
 * 問題文に書かれているコストの計算式は、それぞれのノードごとに、根からの距離とノードの重みをかけたものを合計することと等しい。
 * したがって、全てのノードについて、根からの最短経路を使うようにして木を構成すればよい。
 *
 * オーダーはO(V log E)。
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

typedef long long LL;
const LL INF = 1LL << 50;

struct Edge {
    int from, to;
    LL w;
    Edge *back;
};

bool cmp(const Edge *ea, const Edge *eb) {
    return ea->from < eb->from;
}

Edge _edges[100010];
Edge *edges[100010];
int _pos;

void make_edge(int a, int b, LL w) {
    Edge *ea = edges[_pos] = &_edges[_pos];
    Edge *eb = edges[_pos+1] = &_edges[_pos+1];
    _pos += 2;
    ea->from = eb->to = a;
    eb->from = ea->to = b;
    ea->w = eb->w = w;
    ea->back = eb;
    eb->back = ea;
}

int start_of[50000];
LL weight_of[50000];

bool solve() {
    int V, E;
    scanf("%d %d", &V, &E);
    TIMES(i, V) {
        scanf("%lld", &weight_of[i]);
    }
    _pos = 0;
    TIMES(i, E) {
        int a, b;
        LL w;
        scanf("%d %d %lld", &a, &b, &w);
        --a; --b;
        make_edge(a, b, w);
    }
    if(V == 0) {
        puts("0");
        return true;
    }
    make_edge(V, V, 0);
    sort(edges, edges+E*2+2, cmp);
    fill_n(start_of, V, -1);
    TIMES(i, E*2) {
        //printf("%d->%d\n", edges[i]->from, edges[i]->to);
        if(i == 0) {
            start_of[edges[i]->from] = i;
        } else if(edges[i-1]->from != edges[i]->from) {
            start_of[edges[i]->from] = i;
        }
    }

    static LL memo[50000];
    fill_n(memo, V, INF);
    priority_queue<pair<LL,int> > q;
    q.push(make_pair(0, 0));
    memo[0] = 0;
    while(!q.empty()) {
        const LL cost = -q.top().first;
        const int cur = q.top().second;
        q.pop();
        //printf("%d %lld\n", cur+1, cost);
        if(memo[cur] < cost) continue;
        if(start_of[cur] == -1) continue;
        for(int i = start_of[cur]; edges[i]->from == cur; ++i) {
            const LL nc = cost + edges[i]->w;
            if(memo[edges[i]->to] > nc) {
                memo[edges[i]->to] = nc;
                q.push(make_pair(-nc, edges[i]->to));
            }
        }
    }
    LL ans = 0;
    TIMES(i, V) {
        if(memo[i] == INF) {
            ans = -1;
            break;
        }
        ans += memo[i] * weight_of[i];
    }
    if(ans == -1) {
        puts("No Answer");
    } else {
        printf("%lld\n", ans);
    }
    return true;
}

int main() {
    int N;
    scanf("%d", &N);
    while(N-- && solve()) ;
    return 0;
}
