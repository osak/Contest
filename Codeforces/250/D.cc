//Name: The Child and Sequence
//Level: 5
//Category: Segment Tree
//Note:

/**
 * modがなければ典型的なSegment Treeによるクエリで、O(M log N)で解ける。
 * ここで、modを取ると、その値は変化しないか、1/2以下になるかのどちらかである。
 * したがって、初期値がxのノードは、高々log x回しか変化しないことがわかる。
 *
 * これを利用して、SegmentTreeの各ノードで、区間の和と別に区間内の最大値をもっておき、modの値より小さいものしかない区間は無視するようにする。
 * すると、あるノードはsetされた回数をk回としたとき、高々 k log x 回しかmodによる更新を受けない。
 * よって、modを取る回数は、全体で高々 M log x 回で抑えられる。
 *
 * オーダーは O(M (log N + log X))。
 * ただしXはsetされうる最大値。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;

template <class T>
struct SegmentTree/*{{{*/
{
    vector<T> nodes, max_vals;
    int size;
    SegmentTree(int size) : size(size) {
        nodes.resize(size*4, 0);
        max_vals.resize(size*4, 0);
    }

    // [left, right) に対するクエリ．
    // 現在のノードはpos で， [pl, pr) を表わしている．
    T get_inner(int left, int right, size_t pos, int pl, int pr) {
        if(pr <= left || right <= pl) return 0; // 交差しない
        if(left <= pl && pr <= right) return nodes[pos]; // 完全に含まれる

        const int center = (pl+pr) / 2;
        T lv = get_inner(left, right, pos*2+1, pl, center);
        T rv = get_inner(left, right, pos*2+2, center, pr);
        return lv + rv;
    }

    T get(int left, int right) {
        return get_inner(left, right, 0, 0, size);
    }

    pair<T,T> set_inner(int left, int right, size_t pos, int pl, int pr, T val) {
        if(pr <= left || right <= pl) { // 交差しない
            if(pos >= nodes.size()) return make_pair(0, 0);
            else return make_pair(nodes[pos], max_vals[pos]);
        }
        if(pl+1 == pr) {
            nodes[pos] = val;
            max_vals[pos] = nodes[pos];
            return make_pair(nodes[pos], max_vals[pos]);
        }

        const int center = (pl+pr)/2;
        auto lv = set_inner(left, right, pos*2+1, pl, center, val);
        auto rv = set_inner(left, right, pos*2+2, center, pr, val);
        nodes[pos] = lv.first + rv.first;
        max_vals[pos] = max(lv.second, rv.second);
        return make_pair(nodes[pos], max_vals[pos]);
    }

    void set(int left, int right, T val) {
        set_inner(left, right, 0, 0, size, val);
    }

    pair<T,T> mod_inner(int left, int right, size_t pos, int pl, int pr, T val) {
        if(pr <= left || right <= pl) { // 交差しない
            if(pos >= nodes.size()) return make_pair(0, 0);
            else return make_pair(nodes[pos], max_vals[pos]);
        }
        if(pl+1 == pr) {
            nodes[pos] %= val;
            max_vals[pos] = nodes[pos];
            return make_pair(nodes[pos], max_vals[pos]);
        }
        if(max_vals[pos] < val) {
            return make_pair(nodes[pos], max_vals[pos]);
        }

        const int center = (pl+pr)/2;
        auto lv = mod_inner(left, right, pos*2+1, pl, center, val);
        auto rv = mod_inner(left, right, pos*2+2, center, pr, val);
        nodes[pos] = lv.first + rv.first;
        max_vals[pos] = max(lv.second, rv.second);
        return make_pair(nodes[pos], max_vals[pos]);
    }

    void mod(int left, int right, T val) {
        mod_inner(left, right, 0, 0, size, val);
    }
};/*}}}*/

bool solve() {
    int N, M;
    if(!(cin >> N >> M)) return false;

    SegmentTree<LL> tree(N);
    for(int i = 0; i < N; ++i) {
        int v;
        cin >> v;
        tree.set(i, i+1, v);
    }
    for(int i = 0; i < M; ++i) {
        int op;
        cin >> op;
        if(op == 1) {
            int l, r;
            cin >> l >> r;
            cout << tree.get(l-1, r) << endl;
        } else if(op == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            tree.mod(l-1, r, x);
        } else if(op == 3) {
            int k, x;
            cin >> k >> x;
            tree.set(k-1, k, x);
        }
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
