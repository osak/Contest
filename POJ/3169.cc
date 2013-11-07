//Name: Layout
//Level: 4
//Category: グラフ,Graph,線形計画法,牛ゲー
//Note: 想定解は一部おかしい？

/**
 * 距離D以内の制約は x_b - x_a ≦ D より x_b ≦ x_a + D
 * 距離D以上の制約は x_b - x_a ≧ D より x_a ≦ x_b - D
 * と書ける。
 * また、問題文中の制約より x_1 ≦ x_2 ≦ …… ≦ x_N。
 *
 * このとき、x_b ≦ x_a + Dの形の制約では、x_aに対応するノードからx_bに対応するノードへ
 * コストDの辺を張り、最短経路問題を解くことでこの制約を満たすようなx_a, x_bを探せる
 * ことが分かる。
 * （最短経路問題を解く過程で、d(x_1, x_b) ≦ d(x_1, x_a)+Dとなるため）
 * 距離D以上の制約についても同様。
 *
 * このようにしてグラフを構成し、Bellman-Fordで最短経路を求めればよい。
 * これは、x_1 = 0として、他の変数を矛盾が生じないように決定することに対応する。
 * ここで、負閉路がある場合は矛盾が生じているということなので-1。
 * また、x_1からx_Nに到達できない場合、制約x_1 = 0に関係なくx_Nが決定できるということなので、-2。
 * 
 * 本来は矛盾判定は無限にx_Nを遠くできる判定より先に行うべきなのだが、
 * 到達不能性を先に判定するアルゴリズムで通ってしまう。
 * 4 2 1
 * 2 3 1
 * 3 4 1
 * 2 4 3
 * では本来矛盾が存在するので-1となるはずだが、公式の解でも-2を出力している。
 * （どっちでもACすることを確認したので、テストケースが弱い可能性が高い。）
 *
 * オーダーはO(N(ML+MD+N))。
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

const long long INF = 1LL << 60;
struct Edge {
    int from, to, cost;
};
Edge edges[22000];
int edge_cnt;
long long dist[1001];

bool relax() {
    bool changed = false;
    for(int i = 0; i < edge_cnt; ++i) {
        const Edge &edge = edges[i];
        if(dist[edge.from] == INF) continue;
        const long long nc = dist[edge.from] + edge.cost;
        if(nc < dist[edge.to]) {
            dist[edge.to] = nc;
            changed = true;
        }
    }
    return changed;
}

bool solve() {
    int N, ML, MD;
    if(scanf("%d %d %d", &N, &ML, &MD) == EOF) return false;

    edge_cnt = 0;
    for(int i = 0; i < ML; ++i) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].cost);
    }
    for(int i = 0; i < MD; ++i) {
        scanf("%d %d %d", &edges[ML+i].to, &edges[ML+i].from, &edges[ML+i].cost);
        edges[ML+i].cost *= -1;
    }
    for(int i = 2; i <= N; ++i) {
        edges[ML+MD+i-2].from = i;
        edges[ML+MD+i-2].to = i-1;
        edges[ML+MD+i-2].cost = 0;
    }
    edge_cnt = ML+MD+N-1;
    fill_n(dist, 1001, INF);
    dist[1] = 0;
    for(int i = 0; i < N; ++i) {
        if(!relax()) break;
    }
    if(dist[1] < 0) {
        puts("-1");
    } else if(dist[N] == INF) {
        for(int i = 1; i <= N; ++i) {
            if(dist[i] == INF) dist[i] = 0;
        }
        for(int i = 0; i < N; ++i) {
            if(!relax()) break;
        }
        if(relax()) puts("-1");
        else puts("-2");
    } else {
        printf("%lld\n", dist[N]);
    }
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
