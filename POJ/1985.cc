//Name: Cow Marathon
//Level: 3
//Category: グラフ,Graph,木,直径
//Note:

/**
 * 木の直径を求める問題。
 * 適当な点から最遠点を求め、そこからもう一度最遠点を求めれば、この距離が木の直径（最遠点間距離）である。
 *
 * オーダーはO(N+M)。
 */
#include <cstdio>
#include <queue>
#include <vector>
#include <complex>
#include <list>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef LL Distance;

struct Edge {
    int a, b;
    LL d;

    Edge() : a(-1), b(0) {}
    Edge(int a, int b, const Distance &d) : a(a), b(b), d(d) {}

    bool operator < (const Edge &e) const {
        return a < e.a;
    }
};

int pos_;
Edge edges[80010];
int start_of[40010];

void add_edge(int a, int b, const Distance &d) {
    edges[pos_++] = Edge(a, b, d);
    edges[pos_++] = Edge(b, a, d);
}

pair<int,Distance> farest(int from) {
    static bool visited[40010];
    static pair<int,Distance> stk[40010];
    fill_n(visited, 40010, false);

    pair<int,Distance> res(0, 0);
    int cursor = 0;
    stk[cursor++] = make_pair(from, 0);
    visited[from] = true;
    while(cursor > 0) {
        const int cur = stk[cursor-1].first;
        const Distance cost = stk[cursor-1].second;
        --cursor;
        if(cost > res.second) {
            res = make_pair(cur, cost);
        }
        for(int i = start_of[cur]; edges[i].a == cur; ++i) {
            if(visited[edges[i].b]) continue;
            stk[cursor++] = make_pair(edges[i].b, cost + edges[i].d);
            visited[edges[i].b] = true;
        }
    }
    return res;
}

Distance diameter() {
    pair<int,Distance> tmp = farest(0);
    return farest(tmp.first).second;
}

bool solve() {
    int N, M;
    if(scanf("%d %d", &N, &M) == EOF) return false;
    if(!N && !M) return false;

    pos_ = 0;
    for(int i = 0; i < M; ++i) {
        int a, b, l;
        char dir;
        scanf("%d %d %d %c", &a, &b, &l, &dir);
        --a; --b;
        add_edge(a, b, l);
    }
    add_edge(N, N, -1);
    sort(edges, edges+pos_);

    for(int i = 0; i < pos_; ++i) {
        if(i == 0 || edges[i-1].a != edges[i].a) {
            start_of[edges[i].a] = i;
        }
    }

    printf("%lld\n", diameter());
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
