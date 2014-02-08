//Name: Bad Hair Day
//Level: 3
//Category: SegmentTree,FenwickTree
//Note:

/**
 * ある牛から見える範囲は「自分より右で、自分以上の高さをもつ牛が初めて出てきた箇所」が限界になる。
 * これは牛を右から読んでいきながら、左から右に向けた累積和（ただし和の代わりにmaxを用いる）を管理しておき、
 * 最初にこの累積和が自分の高さ以上になった点が求める場所である。
 * このような累積和はSegmentTreeやFenwickTreeを用いることで、O(log N)で更新・読み出しが可能である。
 * また、単調性から二分探索で目的の箇所が求められる。
 *
 * オーダーはO(N log N)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

template <class T>
struct BIT/*{{{*/
{
  vector<T> tree;
  const int size;
  BIT(int s) : tree(s), size(s) {}
  // i 番目までの要素の累積和
  int read(int i) const
  {
    int sum = 0;
    while (i > 0) {
      sum = max(sum, tree[i]);
      i -= i & -i;
    }
    return sum;
  }

  void add(int i, int v)
  {
    while (i <= size) {
      tree[i] = max(tree[i], v);
      i += (i & -i);
    }
  }
};/*}}}*/

BIT<int> bit(80000);
int buf[80000];

bool solve() {
    int N;
    if(scanf("%d", &N) == EOF) return false;
    if(!N) return false;
    TIMES(i, N) {
        scanf("%d", &buf[i]);
    }

    long long ans = 0;
    for(int i = N; i > 0; --i) {
        int left = i, right = N+1;
        while(left+1 < right) {
            const int center = (left+right) / 2;
            if(bit.read(center) < buf[i-1]) left = center;
            else right = center;
        }
        //printf("%d %d\n", i, right);
        ans += right - i - 1;
        bit.add(i, buf[i-1]);
    }
    printf("%lld\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
