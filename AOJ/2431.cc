//Name: Hose Moving
//Level: 4
//Category: 増加部分列,Segment Tree
//Note:

/*
 * いくつかの要素を適当に移動してソート済みにするとき，移動させない要素群は増加列になっている．
 * したがって，与えられた数列の増加部分列のうち，最も合計値の大きいものを求められれば
 * 数列の数値全てを足したものからこれを引くことで答えを求められる．
 *
 * 最も合計値の大きい増加部分列は，N log(N) で最長増加部分列を求める手法の応用によって求められる．
 * すなわち，SegmentTreeで「数値xを終端とする増加部分列のうち，最大コストを実現したときのコスト」を管理しておく．
 * すると x_iが来たときに区間 [1, x_i) に対して最大値クエリを発行することでこのSegmentTreeをメンテナンスできるようになる．
 *
 * オーダーは O(N log N)．
 * SegmentTreeへのクエリ，更新がそれぞれ log N で完了し，これを N 回行う．
 */
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

// POJ 3264 Balanced Lineup
// AOJ 2431 House Moving
template <class T, class Compare>
struct SegmentTree/*{{{*/
{
  vector<T>& mem;
  vector<int> indexes;
  Compare cmp;
  SegmentTree(vector<T>& cs)
    : mem(cs), indexes(4*cs.size(), -1)
  {
    build(0, 0, cs.size());
  }

  void build(int idx, int left, int right)
  {
    if (left+1 == right) {
      indexes[idx] = left;
    } else {
      const int mid = (left + right)/2;
      build(2*idx+1, left, mid);
      build(2*idx+2, mid, right);
      // minimum in [left, right)
      if (cmp(mem[indexes[2*idx+1]], mem[indexes[2*idx+2]])) {
        indexes[idx] = indexes[2*idx+1];
      } else {
        indexes[idx] = indexes[2*idx+2];
      }
    }
  }

  inline T query_value(int left, int right) const { return mem[query_index(left, right)]; }

  inline int query_index(int left, int right) const { return query_index(left, right, 0, 0, mem.size()); }

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
        if (cmp(mem[l], mem[r])) {
          return l;
        } else {
          return r;
        }
      }
    }
  }

  void update(int idx, T val)
  {
    mem[idx] = val;
    update_index(0, mem.size(), 0, idx);
  }

  void update_index(int left, int right, int i, int idx)
  {
    if (left+1 == right) {
      //indexes[i] = idx;
    } else {
      const int mid = (left+right)/2;
      if (idx < mid) {
        update_index(left, mid, 2*i+1, idx);
      } else {
        update_index(mid, right, 2*i+2, idx);
      }
      if (cmp(mem[indexes[2*i+1]], mem[indexes[2*i+2]])) {
        indexes[i] = indexes[2*i+1];
      } else {
        indexes[i] = indexes[2*i+2];
      }
    }
  }

};/*}}}*/

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    vector<long long> v(N+1, 0);
    SegmentTree<long long, greater<long long> > segtree(v);
    for(int i = 0; i < N; ++i) {
        int X;
        cin >> X;
        long long best = segtree.query_value(0, X);
        segtree.update(X, best + X);
    }
    long long sum = 0;
    for(int i = 1; i <= N; ++i) {
        sum += i;
    }
    cout << sum - segtree.query_value(1, N+1) << endl;
    return 0;
}
