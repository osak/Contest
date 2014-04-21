//Name: Distance Queries
//Level: 3
//Category: グラフ,Graph,木,Tree,LCA,Lowest Common Ancestor
//Note:

/**
 * オーソドックスなLCA問題。
 *
 * オーダーはO(K log M)。
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
    Distance d;

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

pair<int,Distance> ancestor[40010][16];
int depth[40010];

void make_tree(int v, const Edge &e, int d) {
    depth[v] = d;
    int cur = e.a;
    Distance dist = e.d;
    for(int level = 0; cur != -1; cur = ancestor[cur][level++].first) {
        ancestor[v][level] = make_pair(cur, dist);
        dist += ancestor[cur][level].second;
    }
    for(int i = start_of[v]; edges[i].a == v; ++i) {
        if(depth[edges[i].b] != -1) continue;
        make_tree(edges[i].b, edges[i], d+1);
    }
}

bool solve() {
    int N, M;
    if(scanf("%d %d", &N, &M) == EOF) return false;
    if(!N && !M) return false;

    pos_ = 0;
    for(int i = 0; i < N; ++i) {
        depth[i] = -1;
        for(int j = 0; j < 16; ++j) {
            ancestor[i][j] = make_pair(-1, Distance());
        }
    }
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

    make_tree(0, Edge(), 0);

    int K;
    scanf("%d", &K);
    for(int i = 0; i < K; ++i) {
        int from, to;
        scanf("%d %d", &from, &to);
        --from; --to;

        int deeper = depth[from] < depth[to] ? to : from;
        int shallower = depth[from] < depth[to] ? from : to;
        Distance res = 0;
        {
            int diff = depth[deeper] - depth[shallower];
            for(int i = 0; i < 16; ++i) {
                if(diff & (1<<i)) {
                    res += ancestor[deeper][i].second;
                    deeper = ancestor[deeper][i].first;
                }
            }
        }
        int left = -1, right = N;
        while(left+1 < right) {
            const int l = (left + right) / 2;
            int d = deeper, s = shallower;
            for(int i = 0; i < 16; ++i) {
                if(l & (1<<i)) {
                    d = ancestor[d][i].first;
                    s = ancestor[s][i].first;
                    if(d == -1 || s == -1) {
                        break;
                    }
                }
            }
            if(d == -1 || s == -1 || d == s) {
                right = l;
            } else {
                left = l;
            }
        }
        //printf("%d\n", right);
        for(int i = 0; i < 16; ++i) {
            if(right & (1<<i)) {
                res += ancestor[deeper][i].second;
                deeper = ancestor[deeper][i].first;
                res += ancestor[shallower][i].second;
                shallower = ancestor[shallower][i].first;
            }
        }
        printf("%lld\n", res);
    }
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
