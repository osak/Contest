//Name: Surf Smelt Fishing Contest II
//Level: 3
//Category: データ構造,分割統治,Segment Tree
//Note:

/**
 * Segment Treeなどの完全二分木を使って分割統治する。
 * ある葉が更新された時は、ノードを上へたどりながら「そのノードを根とするサブツリーでの優勝者」をメンテナンスする。
 *
 * オーダーは O(Q log N)。
 */
#include <iostream>
#include <vector>

using namespace std;

template <class T>
struct SegmentTree/*{{{*/
{
    vector<T> nodes;
    int size;
    SegmentTree(int size) : size(size) {
        nodes.resize(size*4);
    }

    T get() {
        return nodes[0];
    }

    void add_inner(int target, size_t pos, int pl, int pr, T val) {
        if(pl+1 == pr) {
            nodes[pos].first += val.first;
            nodes[pos].second += val.second;
        } else {
            const int center = (pl+pr)/2;
            if(target < center) {
                add_inner(target, pos*2+1, pl, center, val);
            } else {
                add_inner(target, pos*2+2, center, pr, val);
            }
            const auto lhs = nodes[pos*2+1];
            const auto rhs = nodes[pos*2+2];
            nodes[pos] = max(lhs, rhs);
        }
    }

    void add(int target, T val) {
        add_inner(target, 0, 0, size, val);
    }
};/*}}}*/

int nextpow2(int n) {
    int ans = 1;
    while(ans < n) {
        ans <<= 1;
    }
    return ans;
}

bool solve() {
    int N, Q;
    if(!(cin >> N >> Q)) return false;
    if(!N && !Q) return false;

    SegmentTree<pair<int,int>> tree(nextpow2(N));
    for(int i = 0; i < N; ++i) {
        tree.add(i, make_pair(0, -i));
    }
    for(int i = 0; i < Q; ++i) {
        int a, v;
        cin >> a >> v;
        tree.add(a-1, make_pair(v, 0));
        const auto ans = tree.get();
        cout << -ans.second+1 << ' ' << ans.first << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) ;
    return 0;
}
