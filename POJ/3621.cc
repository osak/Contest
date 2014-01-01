//Name: Sightseeing Cows
//Level: 4
//Category: 数学,平均最大化,グラフ,Graph,二分探索,閉路検出
//Note: 類題POJ3111

/**
 * ある閉路に含まれる頂点と辺を順に書いていくと、
 *   (v1, e1), (v2, e2), ……, (vn, en)
 * のようになる。
 * 問題の目的は、この列上で
 *   k = ∑vi / ∑ei
 * を定義するとき、kが最大になるような閉路を見つけることである。
 *
 * 上の式を変形すると、
 *   k∑ei = ∑vi
 *   ∑(vi - k✕ei) = 0
 * となる。
 * 目的はkの最大化であるから、等号を大なり記号>に置き換えることで
 *   ∑(vi - k✕ei) > 0
 * なる最大のkを探す問題に変換できる。
 *
 * kの値をひとつ決めると、グラフ上にこのような閉路があることは、辺(a, b, c)を通るときに
 * コストがva - k✕cかかるようなグラフ上で正閉路が存在することと等しい。
 * 問題文では同じ頂点を2回以上通っても頂点のコストは加算されないと書いてあるが、同じ頂点を2回目に通る時点で閉路であり、
 * そこで更新が発生しないのであれば無視できる。
 *
 * したがって、kの値を二分探索しながら、Bellman-Fordで閉路検出を行えば良い。
 *
 * オーダーはO(LP log T)。
 * ただしTはスコアの最大値で、制約からT=1000程度である。
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

struct Edge {
    int a, b;
    int cost;

    bool operator < (const Edge &other) const {
        return a < other.a;
    }
};

int funs[1000];
Edge edges[5001];
int start_of[1000];
double cost[1000];

bool relax(int P, double K) {
    bool updated = false;
    TIMES(i, P) {
        const Edge &e = edges[i];
        const double nc = cost[e.a] + funs[e.a] - K*e.cost;
        if(cost[e.b] < nc) {
            cost[e.b] = nc;
            updated = true;
        }
    }
    return updated;
}

bool check(int L, int P, double K) {
    fill_n(cost, L, 0.0);
    TIMES(_, L-1) {
        if(!relax(P, K)) return false;
        //relax(P, K);
    }
    return relax(P, K);
}

bool solve() {
    int L, P;
    if(scanf("%d %d", &L, &P) == EOF) return false;
    if(!L && !P) return false;
    TIMES(i, L) {
        scanf("%d", &funs[i]);
    }
    TIMES(i, P) {
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].cost);
        --edges[i].a;
        --edges[i].b;
    }
    edges[P].a = L+1;
    sort(edges, edges+P);
    fill_n(start_of, L, -1);
    TIMES(i, P) {
        if(i == 0 || edges[i-1].a != edges[i].a) {
            start_of[edges[i].a] = i;
        }
    }
    double left = 0, right = 2000;
    TIMES(_, 22) {
        const double k = (left+right) / 2;
        if(check(L, P, k)) left = k;
        else right = k;
    }
    printf("%.2f\n", left);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
