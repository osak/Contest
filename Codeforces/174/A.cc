#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

// AOJ 2331 A Way to Inveite Friends
// POJ 2777 Count Color
// COCI 2012/2013 #6 Burek
// Codeforces #174(Div.1)A Cows and Sequence
// 更新も O(log N) で可能な SegmentTree．
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

int main() {
    int N;
    scanf("%d", &N);
    SegmentTree<long long> st(1<<18);
    int nelems = 1;
    while(N--) {
        int op;
        scanf("%d", &op);
        if(op == 1) {
            int a, v;
            scanf("%d %d", &a, &v);
            st.add(0, a, v);
        } else if(op == 2) {
            int v;
            scanf("%d", &v);
            st.add(nelems, nelems+1, v);
            ++nelems;
        } else if(op == 3) {
            const int val = st.get(nelems-1, nelems);
            st.add(nelems-1, nelems, -val);
            --nelems;
        }
        printf("%.7f\n", static_cast<double>(st.get(0, nelems)) / nelems);
    }
    return 0;
}
