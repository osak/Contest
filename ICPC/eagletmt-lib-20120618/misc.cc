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

// Suffix Array {{{
struct SAComp {
    const vector<int> *grp;
    int h;
    SAComp(const vector<int> *grp, int h) : grp(grp), h(h) {}

    bool operator ()(int a, int b) const {
        int va = grp->at(a);
        int vb = grp->at(b);
        int vah = a+h < grp->size() ? grp->at(a+h) : INT_MIN;
        int vbh = b+h < grp->size() ? grp->at(b+h) : INT_MIN;
        return (va == vb) ? vah < vbh : va < vb;
    }
};

// Suffix Arrayを構築する．
// A Fast Algorithm for Making Suffix Arrays and for Burrows-Wheeler Transformation
// (Kunihiko Sadakane, 1998)
// の実装．ただし，以下の変更を加えている．
// ・同じグループごとにソートするのではなく，Suffix Array全体を一度にソートする．
// saの中身は開始インデックス．
//
// 計算量O(N (log N)^2)
void suffix_array(const string &str, vector<int> &sa) {
    assert(sa.size() >= str.size());

    int N = str.size();
    vector<int> group(N, 0), next(N, 0);
    for(int i = 0; i < N; ++i) {
        sa[i] = i;
        group[i] = str[i];
    }
    {
        SAComp cmp(&group, 0);
        sort(sa.begin(), sa.end(), cmp);
        next[sa[0]] = 0;
        for(int i = 1; i < N; ++i) {
            next[sa[i]] = next[sa[i-1]] + cmp(sa[i-1], sa[i]);
        }
        group.swap(next);
    }

    for(int h = 1; h < N && group[N-1] != N-1; h <<= 1) {
        //Generate <_{2*h} ordered array from <_{h} ordered array
        //この中身はcmpのコンストラクタ引数以外，上のブロックと同じ．
        SAComp cmp(&group, h);
        sort(sa.begin(), sa.end(), cmp);
        next[sa[0]] = 0;
        for(int i = 1; i < N; ++i) {
            next[sa[i]] = next[sa[i-1]] + cmp(sa[i-1], sa[i]);
        }
        group.swap(next);
    }
}

// 文字列を検索する．
// 複数の候補がある場合，最初に一致したインデックスを返す．
// 計算量O(M log N)
int find(const string &src, const string &str, const vector<int> &sa) {
    int left = 0, right = sa.size();
    while(left < right) {
        int mid = (left+right)/2;
        int res = src.compare(sa[mid], min(src.size()-sa[mid], str.size()), str);
        if(res == 0) return mid;
        if(res < 0) left = mid+1;
        else right = mid;
    }
    return -1;
}/*}}}*/
