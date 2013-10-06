//Name: Perm Query
//Level: 4
//Category: 数論,Segment Tree,Segtree
//Note:

/*
 * インデックスiに着目すると、ここに来る数はある周期kでループする。
 * また、区間[l,r]が終了条件を満たすためには、すべてのl≦i≦rについてちょうどループが終わる、
 * すなわち周期lcm(k_i | l≦i≦r)のループが必要となる。
 *
 * 以上の考察より、区間[l,r]の和は各インデックスごとにばらして考えてよく、インデックスiにおける和は
 *   sum[i] * (lcm(k_i) / k_i)
 * となる。
 * ここで、sum[i]はインデックスiの一周ぶんの合計である。
 * 区間どうしを併合するときも同様の議論が可能なので、全体をSegment Treeで管理することで
 * 高速にクエリを処理することができる。
 *
 * sum*lcmはlong longに収まらない可能性があることに注意。
 *
 * オーダーはO(QNα log N)。
 * ただし、αはLCMの計算コストでO(Σ log k_i)。
 */
#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;
const LL MOD = 1000000007LL;

LL gcd(LL a, LL b) {
    if(a < b) swap(a, b);
    while(b > 0) {
        LL tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

LL lcm(LL a, LL b) {
    if(a == 0 || b == 0) return 0;
    return a / gcd(a, b) * b;
}

struct Tag {
    LL len;
    LL sum;
    Tag() : len(0), sum(0) {}
    Tag(LL len, LL sum) : len(len), sum(sum) {}
};

struct Segtree {
    vector<Tag> data;
    vector<Tag> tree;
    int N;
    Segtree(vector<Tag> &v) : data(v) {
        N = v.size();
        tree.resize(N*4);
        build(1, 0, N);
    }

    void build(int pos, int rl, int rr) {
        if(rl >= rr) return;
        if(rl >= N) return;
        if(rl+1 == rr) {
            tree[pos] = data[rl];
        } else {
            const int center = (rl+rr) / 2;
            build(pos*2, rl, center);
            build(pos*2+1, center, rr);
            tree[pos].len = lcm(tree[pos*2].len, tree[pos*2+1].len);
            LL sum = tree[pos*2].sum * (tree[pos].len / tree[pos*2].len % MOD) % MOD;
            sum += tree[pos*2+1].sum * (tree[pos].len / tree[pos*2+1].len % MOD) % MOD;
            sum %= MOD;
            tree[pos].sum = sum;
        }
    }

    Tag query(int left, int right, int pos, int rl, int rr) {
        if(rr <= left || right <= rl) return Tag(1, 0);
        if(rl >= N) return Tag(1, 0);
        if(rl+1 == rr) return tree[pos];
        if(left <= rl && rr <= right) {
            return tree[pos];
        }
        const int center = (rl+rr) / 2;
        Tag lt = query(left, right, pos*2, rl, center);
        Tag rt = query(left, right, pos*2+1, center, rr);
        LL len = lcm(lt.len, rt.len);
        LL sum = lt.sum * (len / lt.len % MOD) % MOD;
        sum += rt.sum * (len / rt.len % MOD) % MOD;
        return Tag(len, sum%MOD);
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N, Q;
    cin >> N >> Q;
    vector<int> p(N);
    for(auto &i : p) {
        cin >> i;
    }
    vector<Tag> data;
    for(int i = 0; i < N; ++i) {
        Tag tag;
        int cur = i+1;
        do {
            cur = p[cur-1];
            tag.sum += cur;
            ++tag.len;
        } while(cur != i+1);
        data.push_back(tag);
    }
    Segtree segtree(data);
    while(Q--) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        cout << segtree.query(l, r+1, 1, 0, N).sum << endl;
    }
    return 0;
}
