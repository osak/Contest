//Name: A Way to Invite Friends
//Level: 3
//Category: SegmentTree,遅延更新
//Note: 類題: POJ2777

/*
 * 一見二分探索っぽいが，呼ぶことが可能な人数は連続していないので二分探索はできない．
 * 解法はSegmentTree + 遅延更新．
 * SegmentTreeで子区間の値を更新していくとき，更新したい区間に子区間が完全に含まれているときは
 * その子区間だけを更新して，孫区間の更新を後回しにできる．
 * こうすることで更新が区間長 L に対して O(log L) でできるようになる．
 *
 * この不完全な更新が行なわれた区間は，あとで孫区間を訪問するときに回復してやる必要がある．
 * 具体的には，孫区間の和と子区間の値が異なるときに不完全な更新が行なわれたものとみなし，
 * 孫区間に後回しになっていた更新分を配分してやればよい．
 *
 * オーダーは O(N log N)．
 * 区間の登録に O(N log N)，ルックアップに O(N log N)．
 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <class T>
struct SegmentTree/*{{{*/
{
    vector<T> nodes;
    SegmentTree(int size) {
        nodes.resize(size*2, 0);
    }

    void maintain_consistency(int pos) {
        // ノードの値が子の合計と一致しない場合，不完全な更新が行なわれているため
        // 下のノードに伝搬させる．
        int children_sum = nodes[pos*2+1] + nodes[pos*2+2];
        if(children_sum != nodes[pos]) { 
            //cout << "maintain: " << pos << ' ' << nodes[pos] << ' ' << children_sum << endl;
            int diff = nodes[pos] - children_sum;
            nodes[pos*2+1] += diff/2;
            nodes[pos*2+2] += diff/2;
        }
    }

    // [left, right) に対するクエリ．
    // 現在のノードはpos で， [pl, pr) を表わしている．
    int get_inner(int left, int right, int pos, int pl, int pr) {
        //cout << left << ' ' << right << ' ' << pos << ' ' <<  pl << ' ' << pr << endl;
        if(pr <= left || right <= pl) return 0; // 交差しない
        if(left <= pl && pr <= right) return nodes[pos]; // 完全に含まれる

        maintain_consistency(pos);

        const int center = (pl+pr) / 2;
        int lv = get_inner(left, right, pos*2+1, pl, center);
        int rv = get_inner(left, right, pos*2+2, center, pr);
        return lv + rv;
    }

    int get(int left, int right) {
        return get_inner(left, right, 0, 0, nodes.size()/2);
    }

    int add_inner(int left, int right, int pos, int pl, int pr) {
        //cout << left << ' ' << right << ' ' << pos << ' ' <<  pl << ' ' << pr << endl;
        if(pr <= left || right <= pl) return nodes[pos]; // 交差しない
        if(left <= pl && pr <= right) return nodes[pos] += pr-pl; // 完全に含まれる

        maintain_consistency(pos);

        const int center = (pl+pr)/2;
        int lv = add_inner(left, right, pos*2+1, pl, center);
        int rv = add_inner(left, right, pos*2+2, center, pr);
        return nodes[pos] = lv+rv;
    }

    int add(int left, int right) {
        return add_inner(left, right, 0, 0, nodes.size()/2);
    }
};/*}}}*/

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int N;
    cin >> N;
    SegmentTree<int> segtree(1<<17);
    for(int i = 0; i < N; ++i) {
        int minval, maxval;
        cin >> minval >> maxval;
        segtree.add(minval-1, maxval);
    }
    //cout << "Added" << endl;
    //cout << segtree.nodes[0] << ' ' << segtree.nodes[1] << ' ' << segtree.nodes[2] << endl;
    int ans = 0;
    for(int n = N; n >= 0; --n) {
        //cout << segtree.nodes[0] << ' ' << segtree.nodes[1] << ' ' << segtree.nodes[2] << endl;
        const int val = segtree.get(n, n+1);
        //cout << val << endl;
        if(val >= n) {
            ans = n;
            break;
        }
    }
    cout << ans << endl;
    return 0;
}
