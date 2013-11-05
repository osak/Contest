//Name: Fence Obstacle Course
//Level: 3
//Category: 動的計画法,DP,SegmentTree
//Note:

/**
 * 普通にDPすればよいのだが、柵がカバーする座標をすべて調べると間に合わない。
 * ここで、以下の考察を利用する。
 * ・柵によってカバーされたc_n点は次のターンで無効になるため、次のターンで残る点数k_{n+1}は
 * 　　k_{n+1} = k_n - c_n + 2
 * 　と表せる。
 * ・柵は単一の区間のため、1ターンで増える点数は高々1点である。
 * したがって、柵がカバーする座標のうち、到達可能なものだけを調べるようにすると、
 * ここでなめた点はすべて2点に縮約され、点数が減るため高速化ができる。
 * これはSegmentTreeを用いて、柵のある区間で有効なものを左端から取っていくことで実現できる。
 *
 * オーダーはO(NW log W)くらい。
 * ただし、Wは柵の最大幅。
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

    int get_leftmost_index_inner(int left, int right, size_t pos, int pl, int pr) {
        if(pr <= left || right <= pl) return -1;
        if(left <= pl && pr <= right) {
            if(nodes[pos]+stocks[pos] == 0) return -1;
            else if(pl+1 == pr) return pl;
        }
        maintain_consistency(pos);
        const int center = (pl + pr) / 2;
        int lv = get_leftmost_index_inner(left, right, pos*2+1, pl, center);
        if(lv != -1) return lv;
        int rv = get_leftmost_index_inner(left, right, pos*2+2, center, pr);
        return rv;
    }

    int get_leftmost_index(int left, int right) {
        return get_leftmost_index_inner(left, right, 0, 0, size);
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

const int OFFSET = 100000;
int dp[200001];
pair<int,int> fences[50000];
SegmentTree<int> segtree(200001);

inline bool update(int &var, int val) {
    if(var == -1 || val < var) {
        var = val;
        return true;
    }
    return false;
}

bool solve() {
    int N, S;
    if(scanf("%d %d", &N, &S) == EOF) return false;
    for(int i = 0; i < N; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        fences[N-i-1] = make_pair(a+OFFSET, b+OFFSET);
    }
    fill_n(dp, sizeof(dp)/sizeof(int), -1);
    dp[S+OFFSET] = 0;
    segtree.add(S+OFFSET, S+OFFSET+1, 1);
    for(int i = 0; i < N; ++i) {
        bool found = false;
        while(true) {
            int pos = segtree.get_leftmost_index(fences[i].first+1, fences[i].second);
            if(pos == -1) break;
            //printf("%d found: %d\n", i, pos-OFFSET);
            update(dp[fences[i].first], dp[pos] + pos - fences[i].first);
            update(dp[fences[i].second], dp[pos] + fences[i].second - pos);
            dp[pos] = -1;
            segtree.add(pos, pos+1, -1);
            found = true;
        }
        if(found) {
            if(segtree.get(fences[i].first, fences[i].first+1) == 0) segtree.add(fences[i].first, fences[i].first+1, 1);
            if(segtree.get(fences[i].second, fences[i].second+1) == 0) segtree.add(fences[i].second, fences[i].second+1, 1);
        }
    }
    for(int i = 0; i <= 200000; ++i) {
        if(dp[i] == -1) continue;
        update(dp[0+OFFSET], dp[i] + abs(0+OFFSET-i));
    }
    printf("%d\n", dp[0+OFFSET]);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
