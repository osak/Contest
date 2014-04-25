//Name: Distance Statistics
//Level: 4
//Category: グラフ,Graph,木,Tree,Centroid decomposition,重心分解
//Note: TLE厳しい

/**
 * 基本的には木を2つの部分木に分けて、それぞれの部分木内でのペア＋部分木をまたぐペアを計算する。
 * 部分木をまたぐペアについては、部分木Aで根からの距離リストを作っておき、
 * 部分木Bの各ノードに対し、(Aの根までの距離 + A内のノードへの距離)がK以下となるようなものの個数をupper_bound等で求める。
 * 分け方を工夫しない場合は最悪O(N^2 log N)になるが、重心分解することでO(N (log N)^2)となる。
 */
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long LL;
typedef LL Distance;

struct Edge {
    int a, b;
    Distance d;
    bool valid;
    Edge *rev;

    Edge() : a(-1), b(0) {}
} edge_buf[80010];

int pos_;
Edge *edges[80010];
int start_of[40010];

bool cmp_edge(Edge *a, Edge *b) {
    return a->a < b->a;
}

void add_edge(int a, int b, const Distance &d) {
    Edge *ea = edges[pos_] = &edge_buf[pos_];
    Edge *eb = edges[pos_+1] = &edge_buf[pos_+1];
    pos_ += 2;
    ea->a = eb->b = a;
    ea->b = eb->a = b;
    ea->d = eb->d = d;
    ea->rev = eb;
    eb->rev = ea;
    ea->valid = eb->valid = true;
}

int K;
int size[40010];

int calc_size(int v, int parent) {
    size[v] = 1;
    for(int i = start_of[v]; edges[i]->a == v; ++i) {
        if(edges[i]->b == parent) continue;
        if(!edges[i]->valid) continue;
        size[v] += calc_size(edges[i]->b, v);
    }
    return size[v];
}

pair<Edge*,LL> search_centroid(int root) {
    static queue<pair<pair<int,int>,LL> > q;
    int best_diff = 40000;
    int best_edge = -1;
    LL best_dist = 0;
    q.push(make_pair(make_pair(root, -1), 0));
    while(!q.empty()) {
        const int cur = q.front().first.first;
        const int parent = q.front().first.second;
        const LL dist = q.front().second;
        q.pop();
        for(int i = start_of[cur]; edges[i]->a == cur; ++i) {
            if(edges[i]->b == parent || !edges[i]->valid) continue;
            const int sa = size[root] - size[edges[i]->b];
            const int sb = size[edges[i]->b];
            if(abs(sa - sb) < best_diff) {
                best_diff = abs(sa - sb);
                best_edge = i;
                best_dist = dist + edges[i]->d;
            }
            q.push(make_pair(make_pair(edges[i]->b, cur), dist + edges[i]->d));
        }
    }
    return make_pair(edges[best_edge], best_dist);
}

int calc_across(int v, LL vd, LL *buf, int sb) {
    int res = 0;
    static queue<pair<pair<int,int>,LL> > q;
    q.push(make_pair(make_pair(v, -1), vd));
    while(!q.empty()) {
        const int cur = q.front().first.first;
        const int parent = q.front().first.second;
        const LL dist = q.front().second;
        q.pop();
        res += upper_bound(buf, buf+sb, K-dist) - buf;
        for(int i = start_of[cur]; edges[i]->a == cur; ++i) {
            if(edges[i]->b == parent || !edges[i]->valid) continue;
            q.push(make_pair(make_pair(edges[i]->b, cur), dist + edges[i]->d));
        }
    }
    return res;
}

int calc(int root, LL *main_buf, LL *sub_buf) {
    if(calc_size(root, -1) == 1) {
        main_buf[0] = 0;
        return 0;
    }
    pair<Edge*,LL> centroid = search_centroid(root);
    Edge *e = centroid.first;
    e->valid = e->rev->valid = false;
    int res = 0;
    const int sa = size[root] - size[e->b];
    const int sb = size[e->b];
    res += calc(root, main_buf, sub_buf + sb);
    res += calc(e->b, sub_buf, main_buf + sa);
    res += calc_across(e->a, e->d, sub_buf, sb);
    for(int i = 0; i < sb; ++i) {
        main_buf[sa+i] = sub_buf[i] + centroid.second;
    }
    sort(main_buf, main_buf+sa+sb);
    e->valid = e->rev->valid = true;
    return res;
}

bool solve() {
    int N, M;
    if(scanf("%d %d", &N, &M) == EOF) return false;
    if(!N && !M) return false;

    pos_ = 0;
    for(int i = 0; i < N; ++i) {
        size[N] = 0;
    }
    for(int i = 0; i < M; ++i) {
        int a, b, l;
        char dir;
        scanf("%d %d %d %c", &a, &b, &l, &dir);
        --a; --b;
        add_edge(a, b, l);
    }
    add_edge(N, N, -1);
    sort(edges, edges+pos_, cmp_edge);
    for(int i = 0; i < pos_; ++i) {
        if(i == 0 || edges[i-1]->a != edges[i]->a) {
            start_of[edges[i]->a] = i;
        }
    }

    scanf("%d", &K);
    static LL main_buf[40010];
    static LL sub_buf[40010];
    printf("%d\n", calc(0, main_buf, sub_buf));
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
