//Name: Gourmet Grazers
//Level: 3
//Category: 動的計画法,DP,SegmentTree
//Note:

/**
 * Greennessの降順でクエリと商品をソートし、あるクエリを処理するときには
 * それよりGreennessの高いものを全てSegment Treeに入れ、値段の条件を満たすもので一番安いものを出す。
 *
 * オーダーはO(N log (N+M))。
 */
#ifndef ONLINE_JUDGE
//#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

typedef long long LL;

template <class T>
struct SegmentTree/*{{{*/
{
    vector<T> nodes, stocks;
    int size;
    SegmentTree(int size) : size(size) {
        nodes.resize(size*4, 0);
        stocks.resize(size*4, 0);
    }

    void maintain_consistency(size_t pos) {
        if(stocks[pos] != 0) {
            // CAUTION: These expressions depend on following constraint:
            //  size = 2 ** N
            if(pos*2+1 < stocks.size()) stocks[pos*2+1] += stocks[pos] / 2;
            if(pos*2+2 < stocks.size()) stocks[pos*2+2] += stocks[pos] / 2;
            nodes[pos] += stocks[pos];
            stocks[pos] = 0;
        }
    }

    // [left, right) に対するクエリ．
    // 現在のノードはpos で， [pl, pr) を表わしている．
    T get_inner(int left, int right, size_t pos, int pl, int pr) {
        if(pr <= left || right <= pl) return 0; // 交差しない
        if(left <= pl && pr <= right) return nodes[pos] + stocks[pos]; // 完全に含まれる

        maintain_consistency(pos);

        const int center = (pl+pr) / 2;
        T lv = get_inner(left, right, pos*2+1, pl, center);
        T rv = get_inner(left, right, pos*2+2, center, pr);
        return lv + rv;
    }

    T get(int left, int right) {
        return get_inner(left, right, 0, 0, size);
    }

    int get_min_inner(int left, int right, size_t pos, int pl, int pr) {
        if(pr <= left || right <= pl) return -1;
        if(left <= pl && pr <= right && nodes[pos]+stocks[pos] == 0) return -1;
        if(pl+1 == pr) return pl;

        maintain_consistency(pos);
        const int center = (pl+pr) / 2;
        int li = get_min_inner(left, right, pos*2+1, pl, center);
        if(li != -1) return li;
        int ri = get_min_inner(left, right, pos*2+2, center, pr);
        return ri;
    }

    int get_min(int left, int right) {
        return get_min_inner(left, right, 0, 0, size);
    }

    T add_inner(int left, int right, size_t pos, int pl, int pr, T val) {
        if(pr <= left || right <= pl) { // 交差しない
            if(pos >= nodes.size()) return 0;
            else return stocks[pos] + nodes[pos];
        }
        if(left <= pl && pr <= right) {
            stocks[pos] += (pr-pl) * val;
            return stocks[pos] + nodes[pos]; // 完全に含まれる
        }

        maintain_consistency(pos);

        const int center = (pl+pr)/2;
        T lv = add_inner(left, right, pos*2+1, pl, center, val);
        T rv = add_inner(left, right, pos*2+2, center, pr, val);
        return nodes[pos] = lv+rv;
    }

    // Update range [left, right) in O(log N).
    T add(int left, int right, T val) {
        return add_inner(left, right, 0, 0, size, val);
    }
};/*}}}*/

pair<int,int> cows[100000]; // (green, cost)
pair<int,int> grasses[100000]; // (green, cost)
int costs[200000], *costs_end;
SegmentTree<int> segtree(262144);

int get(int v) {
    return static_cast<int>(lower_bound(costs, costs_end, v) - costs);
}

bool solve() {
    int N, M;
    if(scanf("%d %d", &N, &M) == EOF) return false;
    if(!N && !M) return false;

    TIMES(i, N) {
        scanf("%d %d", &cows[i].second, &cows[i].first);
        costs[i] = cows[i].second;
    }
    TIMES(i, M) {
        scanf("%d %d", &grasses[i].second, &grasses[i].first);
        costs[i+N] = grasses[i].second;
    }
    sort(costs, costs+N+M);
    costs_end = unique(costs, costs+N+M);

    sort(cows, cows+N);
    reverse(cows, cows+N);
    sort(grasses, grasses+M);
    reverse(grasses, grasses+M);

    LL ans = 0;
    int grass_pos = 0;
    TIMES(i, N) {
        //printf("%d\n", i);
        while(grass_pos < M && grasses[grass_pos].first >= cows[i].first) {
            const int ci = get(grasses[grass_pos].second);
            segtree.add(ci, ci+1, 1);
            ++grass_pos;
        }
        int lowest = segtree.get_min(get(cows[i].second), costs_end - costs);
        if(lowest != -1) {
            //printf("%d\n", cost_dict_rev[lowest]);
            ans += costs[lowest];
            segtree.add(lowest, lowest+1, -1);
        } else {
            ans = -1;
            break;
        }
    }
    printf("%lld\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
