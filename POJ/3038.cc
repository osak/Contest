//Name: Flying Right
//Level: 4
//Category: 貪欲,Greedy,Segment Tree
//Note:

/**
 * 行きと帰りの便は別々に考えてよいことはすぐ分かる。
 *
 * a < b < c < d である各Farmに対して、[a,d]と[b,c]があったときは、常に[b,c]を優先的に使えばよい。
 * （[b,c]を通るとき、実際に乗っているのが[a,d]でも状態としては変わらず、cで降りたほうがその後有利になるため）
 * 領域が[a,c]と[b,d]のように交差しているときも、同様の議論によって、終点が早いほうを優先的に使うと良い。
 *
 * このとき、ある区間[a,b]で何人乗れるかは、区間に対して一様な加算と最小値の取得をO(log N)でできるようなSegmentTreeを使うことで求められる。
 *
 * オーダーはO(K log N)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

struct Tag {
    int s, e, m;
    
    bool operator <(const Tag &other) const {
        return e < other.e;
    }
};

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
            if(pos*2+1 < stocks.size()) stocks[pos*2+1] += stocks[pos];
            if(pos*2+2 < stocks.size()) stocks[pos*2+2] += stocks[pos];
            nodes[pos] += stocks[pos];
            stocks[pos] = 0;
        }
    }

    // [left, right) に対するクエリ．
    // 現在のノードはpos で， [pl, pr) を表わしている．
    T get_inner(int left, int right, size_t pos, int pl, int pr) {
        if(pr <= left || right <= pl) return 1000000; // 交差しない
        if(left <= pl && pr <= right) return nodes[pos] + stocks[pos]; // 完全に含まれる

        maintain_consistency(pos);

        const int center = (pl+pr) / 2;
        T lv = get_inner(left, right, pos*2+1, pl, center);
        T rv = get_inner(left, right, pos*2+2, center, pr);
        return min(lv, rv);
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
            stocks[pos] += val;
            return stocks[pos] + nodes[pos]; // 完全に含まれる
        }

        maintain_consistency(pos);

        const int center = (pl+pr)/2;
        T lv = add_inner(left, right, pos*2+1, pl, center, val);
        T rv = add_inner(left, right, pos*2+2, center, pr, val);
        return nodes[pos] = min(lv, rv);
    }

    // Update range [left, right) in O(log N).
    T add(int left, int right, T val) {
        return add_inner(left, right, 0, 0, size, val);
    }
};/*}}}*/

int calc(const vector<Tag> &v, int sgn, int N, int cap) {
    SegmentTree<int> segtree(16384);
    const int K = v.size();
    segtree.add(1, N+1, cap);
    int ans = 0;
    TIMES(i, K) {
        const Tag &t = v[i];
        if((t.e - t.s) * sgn < 0) continue;
        int s = t.s, e = t.e;
        if(sgn < 0) swap(s, e);
        const int seat = segtree.get(s, e);
        const int flight = min(seat, t.m);
        ans += flight;
        segtree.add(s, e, -flight);
    }
    return ans;
}

bool solve() {
    int K, N, C;
    if(scanf("%d %d %d", &K, &N, &C) == EOF) return false;
    if(!K && !N && !C) return false;

    vector<Tag> v(K);
    TIMES(i, K) {
        Tag &t = v[i];
        scanf("%d %d %d", &t.s, &t.e, &t.m);
    }
    sort(v.begin(), v.end());

    int ans = 0;
    ans += calc(v, 1, N, C);
    reverse(v.begin(), v.end());
    ans += calc(v, -1, N, C);
    printf("%d\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
