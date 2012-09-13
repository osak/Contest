// vim:set fdm=marker:
struct DisjointSet/*{{{*/
{
  vector<int> parent;

  int root(int x)
  {
    if (parent[x] < 0) {
      return x;
    } else {
      parent[x] = root(parent[x]);
      return parent[x];
    }
  }

  explicit DisjointSet(int n) : parent(n, -1) {}

  bool unite(int x, int y)
  {
    const int a = root(x);
    const int b = root(y);
    if (a != b) {
      if (parent[a] < parent[b]) {
        parent[a] += parent[b];
        parent[b] = a;
      } else {
        parent[b] += parent[a];
        parent[a] = b;
      }
      return true;
    } else {
      return false;
    }
  }

  bool find(int x, int y) { return root(x) == root(y); }
  int size(int x) { return -parent[root(x)]; }
};/*}}}*/

// 1-origin であることに注意．
// bit.add(1, 1); bit.add(2, 2);  bit.add(3, 3) とすると
// - tree[0] = 0
// - tree[1] = 1
// - tree[2] = 3
// - tree[3] = 6
// となる．
template <class T>
struct BinaryIndexedTree/*{{{*/
{
  T tree;
  const int size;
  BinaryIndexedTree(const T& t, int s) : tree(t), size(s) {}
  // i 番目までの要素の累積和
  int read(int i) const
  {
    int sum = 0;
    while (i > 0) {
      sum += tree[i];
      i -= i & -i;
    }
    return sum;
  }

  // i 番目の要素
  int read_single(int i) const
  {
    int sum = tree[i];
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

  void add(int i, int v)
  {
    while (i <= size) {
      tree[i] += v;
      i += (i & -i);
    }
  }
};/*}}}*/

// POJ 3264 Balanced Lineup
template <class Compare>
struct SegmentTree/*{{{*/
{
  const vector<int>& cows;
  vector<int> indexes;
  Compare cmp;
  SegmentTree(const vector<int>& cs)
    : cows(cs), indexes(4*cs.size(), -1)
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
      if (cmp(cows[indexes[2*idx+1]], cows[indexes[2*idx+2]])) {
        indexes[idx] = indexes[2*idx+1];
      } else {
        indexes[idx] = indexes[2*idx+2];
      }
    }
  }

  inline int query_value(int left, int right) const { return cows[query_index(left, right)]; }

  inline int query_index(int left, int right) const { return query_index(left, right, 0, 0, cows.size()); }

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
        if (cmp(cows[l], cows[r])) {
          return l;
        } else {
          return r;
        }
      }
    }
  }
};/*}}}*/

// honeycomb {{{
/*
 * 0:  a a a a a a a a
 * 1:   b b b b b b b
 * 2:  a a a a a a a a
 * のように，左上(0,0)が出張っている場合の配列．
 * 左上が引っ込んでいる場合はEvenとOddを逆にする．
 */
const int DR[6] = {0, -1, -1, 0, 1, 1};
const int DC[2][6] = {
    {-1, -1, 0, 1, 0, -1}, // Even
    {-1, 0, 1, 1, 1, 0}, // Odd
};
// }}}
