//Name: A Simple Problem with Integers
//Level: 3
//Category: SegmentTree
//Note:

/**
 * 更新をバッファできるSegmentTreeを使うと処理できる。
 *
 * オーダーはO(Q log N)。
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
SegmentTree<long long> segtree(131072);

bool solve() {
    int N, Q;
    if(scanf("%d %d", &N, &Q) == EOF) return false;
    if(!N && !Q) return false;

    TIMES(i, N) {
        int v;
        scanf("%d", &v);
        segtree.add(i+1, i+2, v);
    }
    while(Q--) {
        char cmd;
        scanf(" %c", &cmd);
        if(cmd == 'Q') {
            int a, b;
            scanf("%d %d", &a, &b);
            printf("%lld\n", segtree.get(a, b+1));
        } else if(cmd == 'C') {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            segtree.add(a, b+1, c);
        }
    }
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
