//Name: Longest Chain
//Level: 4
//Category: 最長増加列,Longest Increasing Sequence,LIS,SegmentTree
//Note: 

/**
 * 基本的には二次元版のマトリョーシカDP（半順序上の最長増加列問題）と同じように、x座標の順で点を挿入しながらSegmentTreeで最適解を管理すればよい。
 * ここでは残りの次元が2になるので、二次元平面上で、kd木のように平面を4分割して管理するSegmentTreeを実装する。
 * ただし、メモリが足りないので必要なノードだけ作る。
 * こうするとN+M個の点それぞれについて、高々log(座標の上限)個のノードが作られるので、メモリ使用量はO((N+M) log MOD)となる。
 *
 * オーダーは O((N+M) log MOD×(N+M))。
 */
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <map>
#include <array>

using namespace std;

template<typename T>
struct Allocator {
    T *buf;
    const int size_;
    int pos_;

    Allocator(size_t s) : buf(new T[s]), size_(s), pos_(0) {}
    ~Allocator() {
        delete[] buf;
    }

    T* operator ()() {
        assert(pos_ < size_);
        return &buf[pos_++];
    }
};

template<typename T>
struct SegmentTree {
    struct Node {
        T val, buf;
        Node *children[4];
        Node() : val(0), buf(0) {
            fill_n(children, 4, nullptr);
        }
    };

    Node root;
    int size;
    int qxl_, qxr_, qyl_, qyr_; // for querying
    Allocator<Node> allocator_;
    SegmentTree(int size) : size(size), allocator_(4000000) {}

    T update_inner(Node *cur, int xl, int xr, int yl, int yr, T val, int idx) {
        if(xl >= qxr_ || xr <= qxl_ || yl >= qyr_ || yr <= qyl_) {
            return 0;
        }
        if(cur->children[idx] == nullptr) {
            cur->children[idx] = allocator_();
        }
        return update(cur->children[idx], xl, xr, yl, yr, max(cur->buf, val));
    }

    T update(Node *cur, int xl, int xr, int yl, int yr, T val) {
        assert(cur);
        if(xl >= qxr_ || xr <= qxl_ || yl >= qyr_ || yr <= qyl_) {
            return 0;
        }
        if(qxl_ <= xl && xr <= qxr_ && qyl_ <= yl && yr <= qyr_) {
            cur->buf = max(cur->buf, val);
            return max(cur->val, cur->buf);
        }

        const int xm = (xl + xr) / 2;
        const int ym = (yl + yr) / 2;
        cur->val = max(cur->val, update_inner(cur, xl, xm, yl, ym, val, 0));
        cur->val = max(cur->val, update_inner(cur, xl, xm, ym, yr, val, 1));
        cur->val = max(cur->val, update_inner(cur, xm, xr, yl, ym, val, 2));
        cur->val = max(cur->val, update_inner(cur, xm, xr, ym, yr, val, 3));
        return cur->val;
    }

    T update(int xl, int xr, int yl, int yr, T val) {
        qxl_ = xl;
        qxr_ = xr;
        qyl_ = yl;
        qyr_ = yr;
        return update(&root, 0, size, 0, size, val);
    }

    T query(Node *cur, int xl, int xr, int yl, int yr, T thresh) {
        if(cur == nullptr) return 0;
        if(qxl_ <= xl && xr <= qxr_ && qyl_ <= yl && yr <= qyr_) {
            return max(cur->val, cur->buf);
        }
        if(xl >= qxr_ || xr <= qxl_ || yl >= qyr_ || yr <= qyl_) {
            return 0;
        }
        if(max(cur->val, cur->buf) <= thresh) return thresh;

        const int xm = (xl + xr) / 2;
        const int ym = (yl + yr) / 2;
        T val = 0;
        val = max(val, query(cur->children[0], xl, xm, yl, ym, val));
        val = max(val, query(cur->children[1], xl, xm, ym, yr, val));
        val = max(val, query(cur->children[2], xm, xr, yl, ym, val));
        val = max(val, query(cur->children[3], xm, xr, ym, yr, val));
        return val;
    }

    T query(int xl, int xr, int yl, int yr) {
        qxl_ = xl;
        qxr_ = xr;
        qyl_ = yl;
        qyr_ = yr;
        return query(&root, 0, size, 0, size, 0);
    }
};

namespace myrand {
    int a, b, C, M;
    void init(int av, int bv) {
        a = av;
        b = bv;
        C = ~(1<<31);
        M = (1<<16) - 1;
    }

    int r() {
        a = 36969 * (a & M) + (a >> 16);
        b = 18000 * (b & M) + (b >> 16);
        return (C & ((a << 16) + b)) % 1000000;
    }
};

bool solve(bool first) {
    int M, N, A, B;
    if(!(cin >> M >> N >> A >> B)) return false;
    if(!M && !N && !A && !B) return false;

    vector<tuple<int,int,int>> ps;
    for(int i = 0; i < M; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        ps.emplace_back(x, y, z);
    }

    myrand::init(A, B);
    for(int i = 0; i < N; ++i) {
        const int x = myrand::r();
        const int y = myrand::r();
        const int z = myrand::r();
        ps.emplace_back(x, y, z);
    }
    sort(begin(ps), end(ps));

    SegmentTree<int> seg(1000000);
    map<pair<int,int>,int> memo;
    int prevx = -1;
    for(const auto &p : ps) {
        const int x = get<0>(p);
        const int y = get<1>(p);
        const int z = get<2>(p);
        if(x != prevx) {
            for(const auto &m : memo) {
                seg.update(m.first.first, m.first.first+1, m.first.second, m.first.second+1, m.second);
            }
            memo.clear();
            prevx = x;
        }
        const int m = seg.query(0, y, 0, z);
        const auto key = make_pair(y, z);
        memo[key] = max(memo[key], m+1);
    }
    for(const auto &m : memo) {
        seg.update(m.first.first, m.first.first+1, m.first.second, m.first.second+1, m.second);
    }
    cout << seg.query(0, 1000000, 0, 1000000) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
