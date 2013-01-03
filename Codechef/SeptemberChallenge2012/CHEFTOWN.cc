#include <iostream>
#include <cstdio>
#include <vector>
#include <functional>
#include <cstring>

using namespace std;

const int SIZE = 524288; //2^19
inline int cmp(int a, int b) {
    return a < b;
}
//template <class Compare>
struct SegmentTree/*{{{*/
{
    const int *values;
    //vector<int> indexes;
    int indexes[SIZE*2];
    int inv;
    //Compare cmp;
    SegmentTree(int inv) : inv(inv)
    {
        //indexes.resize(SIZE*2, -1);
        memset(indexes, -1, sizeof(indexes));
    }

    void build(int idx, int left, int right)
    {
        if (left+1 == right) {
            indexes[idx] = left;
        } else {
            const int mid = (left + right)>>1;
            const int lidx = (idx<<1)+1;
            const int ridx = (idx<<1)+2;
            build(lidx, left, mid);
            build(ridx, mid, right);
            // minimum in [left, right)
            if (cmp(values[indexes[lidx]], values[indexes[ridx]]) ^ inv) {
                indexes[idx] = indexes[lidx];
            } else {
                indexes[idx] = indexes[ridx];
            }
        }
    }

    inline int query_value(int left, int right) const { return values[query_index(left, right)]; }

    inline int query_index(int left, int right) const { return query_index(left, right, 0, 0, SIZE); }

    int query_index(int left, int right, int i, int a, int b) const
    {
        // [a, b) is the range of indexes[i]
        if (b <= left || right <= a) {
            // does not intersect
            return -1;
        } else if (left <= a && b <= right) {
            // contains
            return indexes[i];
        } else {
            const int m = (a+b)/2;
            const int l = query_index(left, right, 2*i+1, a, m);
            const int r = query_index(left, right, 2*i+2, m, b);
            if (l == -1) {
                return r;
            } else if (r == -1) {
                return l;
            } else {
                if (cmp(values[l], values[r]) ^ inv) {
                    return l;
                } else {
                    return r;
                }
            }
        }
    }
};/*}}}*/

int H[SIZE];
SegmentTree min_st(0);
SegmentTree max_st(1);
int main() {
    int N, W;
    scanf("%d %d", &N, &W);
    int *ptr = H;
    for(int i = 0; i < N; ++i) {
        scanf("%d", ptr++);
    }
    min_st.values = max_st.values = H;
    min_st.build(0, 0, N);
    max_st.build(0, 0, N);
    int ans = 0;
    for(int r = W; r <= N; ++r) {
        const int l = r - W;
        const int minval = H[min_st.query_index(l, r, 0, 0, N)];
        const int maxval = H[max_st.query_index(l, r, 0, 0, N)];
        if(maxval - minval == W-1) ++ans;
    }
    printf("%d\n", ans);
    return 0;
}
