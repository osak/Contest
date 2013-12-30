//Name: Roadblocks
//Level: 3
//Category: グラフ,Graph,最短経路
//Note:

/**
 * 2つ目の最小値まで覚えてダイクストラ。
 *
 * オーダーはO(N + R log R)。
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

struct Edge {
    int from, to;
    LL cost;
};

bool cmp(const Edge *a, const Edge *b) {
    return a->from < b->from;
}

Edge _buf[200002];
int _pos;
Edge *edges[200002];
int start_of[5000];

void make_edge(int from, int to, LL cost) {
    Edge *ea = edges[_pos] = &_buf[_pos];
    Edge *eb = edges[_pos+1] = &_buf[_pos+1];
    _pos += 2;
    ea->from = eb->to = from;
    ea->to = eb->from = to;
    ea->cost = eb->cost = cost;
}

const LL INF = 1LL << 50;
bool solve() {
    int N, R;
    if(scanf("%d %d", &N, &R) == EOF) return false;
    if(!N && !R) return false;

    _pos = 0;
    TIMES(_, R) {
        int a, b, d;
        scanf("%d %d %d", &a, &b, &d);
        make_edge(a-1, b-1, d);
    }
    make_edge(N, N, 0);
    sort(edges, edges+2*R, cmp);
    fill_n(start_of, N, -1);
    TIMES(i, 2*R) {
        if(i == 0 || edges[i]->from != edges[i-1]->from) {
            start_of[edges[i]->from] = i;
        }
    }

    static LL memo[5000][2];
    TIMES(i, N) {
        memo[i][0] = memo[i][1] = INF;
    }
    priority_queue<pair<LL,int> > q;
    q.push(make_pair(0, 0));
    memo[0][0] = 0;
    while(!q.empty()) {
        const LL cost = -q.top().first;
        const int cur = q.top().second;
        q.pop();
        if(cur == N-1 && cost == memo[cur][1]) break;
        if(cost > memo[cur][1]) continue;
        if(start_of[cur] == -1) continue;
        for(int i = start_of[cur]; edges[i]->from == cur; ++i) {
            const int to = edges[i]->to;
            const LL nc = cost + edges[i]->cost;
            if(nc < memo[to][0]) {
                memo[to][1] = memo[to][0];
                memo[to][0] = nc;
                q.push(make_pair(-nc, to));
            } else if(nc != memo[to][0] && nc < memo[to][1]) {
                memo[to][1] = nc;
                q.push(make_pair(-nc, to));
            }
        }
    }
    printf("%lld\n", memo[N-1][1]);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
