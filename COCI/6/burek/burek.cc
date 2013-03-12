//#define _GLIBCXX_DEBUG

#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cassert>

using namespace std;

const int INF = 1000000000;

template <class T>
struct SegmentTree/*{{{*/
{
    vector<T> nodes, stocks;
    int size;
    SegmentTree(int size) : size(size) {
        assert(__builtin_popcount(size) == 1);
        nodes.resize(size*4, 0);
        stocks.resize(size*4, 0);
    }

    void maintain_consistency(int pos) {
        /*
        // ノードの値が子の合計と一致しない場合，不完全な更新が行なわれているため
        // 下のノードに伝搬させる．
        int children_sum = nodes[pos*2+1] + nodes[pos*2+2];
        if(children_sum != nodes[pos]) { 
            //cout << "maintain: " << pos << ' ' << nodes[pos] << ' ' << children_sum << endl;
            int diff = nodes[pos] - children_sum;
            nodes[pos*2+1] += diff/2;
            nodes[pos*2+2] += diff/2;
        }
        */
        if(stocks[pos] > 0) {
            // These statements are depends on following constraint:
            //  size = 2**n
            if(pos*2+1 < stocks.size()) stocks[pos*2+1] += stocks[pos] / 2;
            if(pos*2+2 < stocks.size()) stocks[pos*2+2] += stocks[pos] / 2;
            nodes[pos] += stocks[pos];
            stocks[pos] = 0;
        }
    }

    // [left, right) に対するクエリ．
    // 現在のノードはpos で， [pl, pr) を表わしている．
    T get_inner(int left, int right, int pos, int pl, int pr) {
        //cout << left << ' ' << right << ' ' << pos << ' ' <<  pl << ' ' << pr << endl;
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

    T add_inner(int left, int right, int pos, int pl, int pr) {
        //cout << left << ' ' << right << ' ' << pos << ' ' <<  pl << ' ' << pr << endl;
        if(pr <= left || right <= pl) { // 交差しない
            if(pos < nodes.size()) return stocks[pos] + nodes[pos];
            else return 0;
        }
        if(left <= pl && pr <= right) {
            //cout << "tail: " << pl << ' ' << pr << endl;
            stocks[pos] += pr-pl;
            return stocks[pos] + nodes[pos]; // 完全に含まれる
        }

        maintain_consistency(pos);

        const int center = (pl+pr)/2;
        T lv = add_inner(left, right, pos*2+1, pl, center);
        T rv = add_inner(left, right, pos*2+2, center, pr);
        return nodes[pos] = lv+rv;
    }

    T add(int left, int right) {
        return add_inner(left, right, 0, 0, size);
    }
};/*}}}*/

int main() {
    int N;
    scanf("%d", &N);
    SegmentTree<int> xtree(1<<20), ytree(1<<20);
    for(int i = 0; i < N; ++i) {
        int l = INF, r = 0, b = INF, t = 0;
        for(int j = 0; j < 3; ++j) {
            int x, y;
            scanf("%d %d", &x, &y);
            l = min(l, x); r = max(r, x);
            b = min(b, y); t = max(t, y);
        }
        xtree.add(l+1, r);
        ytree.add(b+1, t);
    }

    int M;
    scanf("%d", &M);
    while(M--) {
        char axis;
        int pos;
        scanf(" %c = %d", &axis, &pos);
        int ans = 0;
        if(axis == 'x') {
            ans = xtree.get(pos, pos+1);
        } else {
            ans = ytree.get(pos, pos+1);
        }
        printf("%d\n", ans);
    }
    return 0;
}
