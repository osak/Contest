//Name: Remmarguts' Date
//Level: 3
//Category: グラフ,Graph,k-最短路,k-shortest path,A*
//Note: 1頂点からなるパスは数えない

/**
 * k-最短路を求める問題。
 * 問題のサイズが小さければ、各頂点へのk-最短距離を覚えながらBellman-Fordなどでも解ける。
 * この問題ではサイズが大きいので、A*を使って効率よく探索していく。
 * A*のヒューリスティックとしては、Tまでの通常の意味での最短距離を使えばよい。
 *
 * 普通はパスというと単一頂点のものも長さ0として数えるが、この問題では数えないらしく、
 * S == Tのときだけ特別な処理が必要になる。
 * （問題文からは読み取れない）
 */
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    int to, cost;

    Edge() {}
    Edge(int t, int c) : to(t), cost(c) {}
};

struct Tag {
    int pos;
    long long cost, h;
    Tag() {}
    Tag(int p, long long c, long long h) : pos(p), cost(c), h(h) {}

    bool operator <(const Tag &other) const {
        return cost+h > other.cost+other.h; // reversed order
    }
};

int N, S, T, K;
vector<Edge> graph[1000];
vector<Edge> rev_graph[1000];
long long h[1000];
const long long INF = 1000000000LL;

void calc_h() {
    fill_n(h, N, INF);
    priority_queue<Tag> q;
    q.push(Tag(T, 0, 0));
    h[T] = 0;
    while(!q.empty()) {
        const Tag cur = q.top();
        q.pop();
        if(h[cur.pos] < cur.cost) continue;
        const int M = rev_graph[cur.pos].size();
        for(int i = 0; i < M; ++i) {
            const int np = rev_graph[cur.pos][i].to;
            const long long nc = cur.cost + rev_graph[cur.pos][i].cost;
            if(h[np] > nc) {
                h[np] = nc;
                q.push(Tag(np, nc, 0));
            }
        }
    }
}

int calc() {
    priority_queue<Tag> q;
    q.push(Tag(S, 0, h[S]));
    int cnt = 0;
    while(!q.empty()) {
        const Tag cur = q.top();
        q.pop();
        if(cur.pos == T) {
            if(++cnt == K) return cur.cost;
        }
        const int M = graph[cur.pos].size();
        for(int i = 0; i < M; ++i) {
            const int np = graph[cur.pos][i].to;
            const int nc = cur.cost + graph[cur.pos][i].cost;
            if(h[np] == INF) continue; // Unreachable
            q.push(Tag(np, nc, h[np]));
        }
    }
    return -1;
}

bool solve() {
    int M;
    if(scanf("%d %d", &N, &M) == EOF) return false;
    for(int i = 0; i < N; ++i) {
        graph[i].clear();
        rev_graph[i].clear();
    }
    while(M--) {
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        --a; --b;
        graph[a].push_back(Edge(b, t));
        rev_graph[b].push_back(Edge(a, t));
    }
    scanf("%d %d %d", &S, &T, &K);
    --S; --T;
    if(S == T) {
        ++K;
    }
    calc_h();
    printf("%d\n", calc());
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
