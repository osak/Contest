//Name: Walking Race
//Level: 3
//Category: DP,スライド最小値
//Note: TLE厳しい

/**
 * 木の上である点から最遠の点を高速に求める問題と、スライドする区間での
 * 最大値・最小値クエリに高速で答える問題の2段構成。
 *
 * 前半は2パスのDPで求めることができる。
 * 1回目では、葉から根へ上って行きながら、下に行くときの最遠距離を求める。
 * これは dp_down[i] = max(dp_down[child_of[i]] + c(i, child_of[i]))。
 * 2回めでは、根から葉へ降りて行きながら、上に行くときの最遠距離を求める。
 * これは dp_up[i] = max(dp_up[root_of[i]], dp_down[child_of[root_of[i]]]) + c(i, root_of[i])
 * ただし、2回めのdp_downでは、自分自身に戻ってくるパスは使わないようにする必要がある。
 *
 * スライド最小値はdequeを使い、この中で最小値候補が常に降順に並ぶようにメンテナンスするとO(N)で解ける。
 * 最大値についても同様。
 *
 * オーダーはO(N)。
 * ただし、TLEとMLEが非常に厳しく、STLを使うと通らない。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <deque>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

typedef long long LL;

struct Edge {
    int from, to, cost;

    bool operator <(const Edge &other) const {
        return from < other.from;
    }
};

const int MAX_N = 1000000;
const int MAX_LOG_N = 20;
int N;
Edge edges[MAX_N*2+1];
Edge *start_of[MAX_N+1];
LL dp_down[MAX_N][2], dp_up[MAX_N];
int dp_down_from[MAX_N];
LL dp[MAX_N];
int root_of[MAX_N];
int ord[MAX_N];
pair<int,LL> q[MAX_N];
LL maxq[2*MAX_N+100], minq[2*MAX_N+100];
int maxq_f, maxq_b, minq_f, minq_b;

void init(int pos, int root) {
    int q_pos = 0;
    root_of[pos] = root;
    int cnt = 0;
    q[q_pos++] = make_pair(pos, root);
    while(q_pos > 0) {
        --q_pos;
        const int cur = q[q_pos].first;
        const int cur_root = q[q_pos].second;
        ord[cnt++] = cur;
        for(const Edge *edge = start_of[cur]; edge->from == cur; ++edge) {
            if(edge->to == cur_root) continue;
            root_of[edge->to] = cur;
            q[q_pos++] = make_pair(edge->to, cur);
        }
    }
}

void build_down() {
    for(int i = N-1; i >= 0; --i) {
        const int cur = ord[i];
        for(const Edge *edge = start_of[cur]; edge->from == cur; ++edge) {
            if(edge->to == root_of[cur]) continue;
            for(int k = 0; k < 2; ++k) {
                const LL d = dp_down[edge->to][k] + edge->cost;
                if(d > dp_down[cur][0]) {
                    dp_down[cur][1] = dp_down[cur][0];
                    dp_down[cur][0] = d;
                    dp_down_from[cur] = edge->to;
                    break;
                } else if(d > dp_down[cur][1]) {
                    dp_down[cur][1] = d;
                }
            }
            //printf("%d %lld %lld\n", cur, dp_down[cur][0], dp_down[cur][1]);
        }
    }
}

void build_up() {
    for(int i = 0; i < N; ++i) {
        const int cur = ord[i];
        for(const Edge *edge = start_of[cur]; edge->from == cur; ++edge) {
            if(edge->to == root_of[cur]) continue;
            const LL d = (edge->to == dp_down_from[cur]) ? dp_down[cur][1] : dp_down[cur][0];
            dp_up[edge->to] = max(dp_up[cur], d) + edge->cost;
        }
    }
}

bool solve() {
    int M;
    if(scanf("%d %d", &N, &M) == EOF) return false;
    for(int i = 0; i < N; ++i) {
        dp_down[i][0] = dp_down[i][1] = 0;
        dp_up[i] = 0;
    }
    for(int i = 0; i < N-1; ++i) {
        int f, d;
        scanf("%d %d", &f, &d);
        --f;
        edges[i*2].from = i+1;
        edges[i*2].to = f;
        edges[i*2].cost = d;
        edges[i*2+1].from = f;
        edges[i*2+1].to = i+1;
        edges[i*2+1].cost = d;
    }
    sort(edges, edges+(N-1)*2);
    edges[(N-1)*2].from = -1;
    fill_n(start_of, N, (Edge*)NULL);
    start_of[0] = edges;
    for(int i = 1; i < (N-1)*2; ++i) {
        if(edges[i].from != edges[i-1].from) {
            start_of[edges[i].from] = edges+i;
        }
    }
    start_of[N] = edges+(N-1)*2;
    init(0, -1);
    build_down();
    build_up();
    for(int i = 0; i < N; ++i) {
        //printf("%lld %lld\n", dp_up[i], dp_down[i][0]);
        dp[i] = max(dp_up[i], dp_down[i][0]);
    }

    int ans = 0;
    int cur_tail = 0;
    maxq_f = maxq_b = MAX_N+50;
    minq_f = minq_b = MAX_N+50;
    for(int i = 0; i < N; ++i) {
        while(maxq_f < maxq_b && maxq[maxq_f] < dp[i]) ++maxq_f;
        maxq[--maxq_f] = dp[i];
        while(minq_f < minq_b && minq[minq_f] > dp[i]) ++minq_f;
        minq[--minq_f] = dp[i];
        while(maxq[maxq_b-1] - minq[minq_b-1] > M) {
            if(maxq[maxq_b-1] == dp[cur_tail]) --maxq_b;
            if(minq[minq_b-1] == dp[cur_tail]) --minq_b;
            ++cur_tail;
        }
        ans = max(ans, i - cur_tail + 1);
    }
    printf("%d\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
