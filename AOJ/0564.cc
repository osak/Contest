//Name: Bug Party
//Level: 4
//Category: 二分探索,Fenwick Tree
//Note:

/**
 * 使う細菌の個数kを決めると、
 *   Σa_i_j ≦ k × min_j(b_i_j) (j ∈ S, |S| = k)
 * なるSを求める問題になる。
 * また、k個の細菌をシャーレに入れることができれば、それより少ない個数の
 * 組み合わせも実現可能であるから、kの値は二分探索できる。
 *
 * ここで更にb^* = min_j(b_i_j)を決めると、このような組み合わせが作れるかどうかは
 * b_i ≧ b^* なるb_iをもつ細菌のうち、a_iの小さいものから順にk個を選んでいったときに
 * 制約を満たしているかどうかを確認することで判定できる。
 * つまり、興味があるのはb_*より大きいa_iの合計と、その個数がk個になるタイミングであり、
 * これらはどちらも累積和の形なので、Fenwick Treeを用いて管理できる。
 *
 * 具体的には、a_iの小さいものから順に、インデックスb_iにa_iを加算していく。
 * また、同様にして個数も管理する。
 * 1つ細菌を加えるごとに、二分探索を用いて、「それより大きいb_iをもつ細菌の個数」がちょうどkになったb_iを求める。
 * これが制約を満たしていれば、k個の細菌をシャーレに入れることが可能である。
 *
 * オーダーは O(N (log N)^3)。
 * ナイーブに見積もると14億ループ程度回る計算になるが、k個の細菌を入れられるときの
 * 判定を早く切り上げることができるためか、オーダーの割には高速に動作する。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;
#define TIMES(i_, n_) for(int i_ = 0; i_ < n_; ++i_)

template <class T>
struct BinaryIndexedTree/*{{{*/
{
    vector<T> tree;
    const int size;
    BinaryIndexedTree(int s) : tree(s), size(s) {}
    // i 番目までの要素の累積和
    T read(int i) const
    {
        T sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= i & -i;
        }
        return sum;
    }

    // i 番目の要素
    T read_single(int i) const
    {
        T sum = tree[i];
        if (i > 0) {
            const int z = i - (i & -i);
            --i;
            while (i != z) {
                sum -= tree[i];
                i -= (i & -i);
            }
        }
        return sum;
    }

    void add(int i, T v)
    {
        while (i <= size) {
            tree[i] += v;
            i += (i & -i);
        }
    }

    int search(T v) {
        int left = 0, right = size;
        while(left+1 < right) {
            const int center = (left+right) / 2;
            if(read(center) < v) {
                left = center;
            } else {
                right = center;
            }
        }
        if(right == size || read(right) != v) return -1;
        return right;
    }
};/*}}}*/

struct Bug {
    LL a, b;
};

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<Bug> bugs(N);
    TIMES(i, N) {
        cin >> bugs[i].a >> bugs[i].b;
    }
    sort(bugs.begin(), bugs.end(), [](const Bug a, const Bug b) {
            return a.a < b.a;
            });
    int ans = 0;
    int left = 0, right = N+1;
    while(left+1 < right) {
        const int k = (left + right) / 2;
        BinaryIndexedTree<LL> bit(100002);
        BinaryIndexedTree<int> bit_cnt(100002);
        for(const auto &bug : bugs) {
            const int idx = 100001 - int(bug.b);
            bit.add(idx, bug.a);
            bit_cnt.add(idx, 1);
            const auto lim = bit_cnt.search(k);
            //cout << k << ' ' << (100001 - lim) << ' ' << bit.read(lim) << ' ' << bit_cnt.read(lim) << endl;
            if(lim != -1 && bit.read(lim) <= (LL)k * (100001 - lim)) {
                ans = k;
                break;
            }
        }
        if(ans == k) {
            left = k;
        } else {
            right = k;
        }
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}

