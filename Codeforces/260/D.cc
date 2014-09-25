//Name: Serega and Fun
//Level: 4
//Category: Range Minimum Query,RMQ,平方分割,Square Decomposition
//Note:

/**
 * Decomposing array into bins of √N elemnts and use deque for each bin, 
 * rotation and counting elements can be performed in O(√N).
 * - Rotation: Except the leftmost and rightmost bins, the effect of rotation is just shifting one element to left.
 *             It can be implemented by pushing one element to one end and popping one element from another end,
 *             each runs in O(1) time.
 *             For bins at both ends, pushing and popping at most √N elements is required, though it costs O(√N).
 * - Counting: For each pop and push operation, maintaining the number of k in one bin is O(1) (Just increase/decrease!)
 *             If the query covers bin[i] completely, you can use this number instead of traversing all elements in the bin.
 *             Though bins at both ends need special treatment, whole procedure costs at most O(√N).
 * Note that special treatment is needed for bins at both ends, especially l and r fall in the same bin.
 *
 * Totally, complexity is O(Q√N).
 */
#include <iostream>
#include <deque>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int S = 320;
struct SquareDecomp {
    int cnt[S][100001];
    deque<int> bin[S];

    SquareDecomp(const vector<int> &v) {
        memset((int*)cnt, sizeof(cnt)/sizeof(int), 0);
        int bi = 0;
        for(int i = 0; i < v.size(); ++i) {
            bin[bi].push_back(v[i]);
            cnt[bi][v[i]]++;
            if(i % S == S-1) ++bi;
        }
        if(bin[bi].size() > 0) {
            const int rem = S - bin[bi].size();
            for(int i = 0; i < rem; ++i) {
                bin[bi].push_back(0);
            }
        }
    }

    int bin_of(int idx) const {
        return idx / S;
    }

    int index_in_bin(int idx) const {
        return idx % S;
    }

    void rotate_in_same_bin(int l, int r) {
        const int bl = bin_of(l);
        const int li = index_in_bin(l);
        const int ri = index_in_bin(r);
        deque<int> head;
        for(int i = 0; i < li; ++i) {
            head.push_back(bin[bl].front());
            bin[bl].pop_front();
        }
        deque<int> buf;
        for(int i = li; i <= ri; ++i) {
            buf.push_back(bin[bl].front());
            bin[bl].pop_front();
        }
        buf.push_front(buf.back());
        buf.pop_back();
        while(!buf.empty()) {
            bin[bl].push_front(buf.back());
            buf.pop_back();
        }
        while(!head.empty()) {
            bin[bl].push_front(head.back());
            head.pop_back();
        }
    }

    void rotate(int l, int r) {
        const int bl = bin_of(l);
        const int br = bin_of(r);
        if(bl == br) {
            rotate_in_same_bin(l, r);
        } else {
            deque<int> buf;
            const int ri = index_in_bin(r);
            for(int i = 0; i <= ri; ++i) {
                buf.push_back(bin[br].front());
                bin[br].pop_front();
            }
            const int v = buf.back();
            buf.pop_back();
            while(!buf.empty()) {
                bin[br].push_front(buf.back());
                buf.pop_back();
            }
            cnt[br][v]--;
            for(int i = br-1; i > bl; --i) {
                const int vv = bin[i].back();
                bin[i].pop_back();
                cnt[i][vv]--;
                bin[i+1].push_front(vv);
                cnt[i+1][vv]++;
            }
            const int li = index_in_bin(l);
            for(int i = S-1; i >= li; --i) {
                buf.push_back(bin[bl].back());
                bin[bl].pop_back();
            }
            bin[bl+1].push_front(buf.front());
            cnt[bl+1][buf.front()]++;
            cnt[bl][buf.front()]--;
            buf.pop_front();
            bin[bl].push_back(v);
            cnt[bl][v]++;
            while(!buf.empty()) {
                bin[bl].push_back(buf.back());
                buf.pop_back();
            }
        }
    }

    int getcnt_in_same_bin(int l, int r, int v) const {
        const int bl = bin_of(l);
        int res = 0;
        for(int i = index_in_bin(l); i <= index_in_bin(r); ++i) {
            res += bin[bl][i] == v;
        }
        return res;
    }

    int getcnt(int l, int r, int v) const {
        const int bl = bin_of(l);
        const int br = bin_of(r);
        if(bl == br) {
            return getcnt_in_same_bin(l, r, v);
        }
        int res = 0;
        for(int i = index_in_bin(l); i < S; ++i) {
            res += bin[bl][i] == v;
        }
        for(int i = bl+1; i < br; ++i) {
            res += cnt[i][v];
        }
        for(int i = 0; i <= index_in_bin(r); ++i) {
            res += bin[br][i] == v;
        }
        return res;
    }
};

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<int> v(N);
    for(int i = 0; i < N; ++i) {
        cin >> v[i];
    }
    SquareDecomp *sd = new SquareDecomp(v);
    int Q;
    cin >> Q;
    int lastans = 0;
    while(Q--) {
        int qi, l, r;
        cin >> qi >> l >> r;
        l = (l + lastans - 1) % N + 1;
        r = (r + lastans - 1) % N + 1;
        if(l > r) swap(l, r);
        --l; --r;

        if(qi == 1) {
            sd->rotate(l, r);
        } else if(qi == 2) {
            int k;
            cin >> k;
            k = (k + lastans - 1) % N + 1;
            lastans = sd->getcnt(l, r, k);
            cout << lastans << endl;
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
