//Name: ターゲット
//Level: 4
//Category: 動的計画法,DP,最長増加部分列,LIS,Segment Tree,Fenwick Tree
//Note:

/*
 * 円の右端でソートすると、この順に選んでいけば右端は包含条件を勝手に満たすようになる。
 * この状態で左端も包含条件を満たすようにするためには、左端も単調減少である必要がある。
 * すなわち、左端の最長減少部分列をとればよい。
 * これはFenwick Treeなどを用いることでO(N log N)で解ける。
 *
 * オーダーはO(N log N)。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Tag {
    int l, r;
    Tag() {}
    Tag(int l, int r) : l(l), r(r) {}

    bool operator <(const Tag &other) const {
        if(r != other.r) return r < other.r;
        return l < other.l;
    }

    bool operator ==(const Tag &other) const {
        return l == other.l && r == other.r;
    }
};

struct FenwickTree {
    vector<int> buf;

    FenwickTree(int N) {
        buf.resize(N, 0);
    }

    int read(int pos) {
        int res = 0;
        while(pos > 0) {
            res = max(res, buf[pos]);
            pos -= (pos & -pos);
        }
        return res;
    }

    int update(int pos, int val) {
        const int N = buf.size();
        while(pos < N) {
            buf[pos] = max(buf[pos], val);
            pos += (pos & -pos);
        }
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    vector<Tag> tags(N);
    vector<int> ls(N);
    for(int i = 0; i < N; ++i) {
        int x, r;
        cin >> x >> r;
        ls[i] = tags[i].l = x - r;
        tags[i].r = x + r;
    }
    sort(tags.begin(), tags.end());
    tags.erase(unique(tags.begin(), tags.end()), tags.end());
    N = tags.size();
    sort(ls.begin(), ls.end());
    ls.erase(unique(ls.begin(), ls.end()), ls.end());
    const int M = ls.size();
    map<int,int> dict;
    for(int i = 0; i < M; ++i) {
        dict[ls[i]] = i+1;
    }
    FenwickTree ft(M+1);
    for(int i = 0; i < N; ++i) {
        const int l = M+1 - dict[tags[i].l];
        ft.update(l, ft.read(l-1) + 1);
    }
    cout << ft.read(M) << endl;
    return 0;
}
