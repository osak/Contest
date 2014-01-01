//Name: Gourmet Grazers
//Level: 3
//Category: 動的計画法,DP,FenwickTree
//Note:

/**
 * Greennessの降順でクエリと商品をソートし、あるクエリを処理するときには
 * それよりGreennessの高いものを全てBITに入れ、値段の条件を満たすもので一番安いものを出す。
 *
 * オーダーはO(N (log (N+M))^2)。
 */
#ifndef ONLINE_JUDGE
//#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

typedef long long LL;

template <class T>
struct BIT/*{{{*/
{
  T tree[200001];
  const int size;
  BIT(int s) : size(s) {}
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

  int find_min(int v) {
      if(read_single(v) != 0) return v;

      const int threshold = read(v);
      int left = v, right = size-1;
      while(left+1 < right) {
          const int mid = (left+right) / 2;
          if(read(mid) > threshold) {
              right = mid;
          } else {
              left = mid;
          }
      }
      return right;
  }
};/*}}}*/

pair<int,int> cows[100000]; // (green, cost)
pair<int,int> grasses[100000]; // (green, cost)
int costs[200000], *costs_end;
BIT<int> bit(200000+1);

int get(int v) {
    return static_cast<int>(lower_bound(costs, costs_end, v) - costs) + 1;
}

bool solve() {
    int N, M;
    if(scanf("%d %d", &N, &M) == EOF) return false;
    if(!N && !M) return false;

    TIMES(i, N) {
        scanf("%d %d", &cows[i].second, &cows[i].first);
        costs[i] = cows[i].second;
    }
    TIMES(i, M) {
        scanf("%d %d", &grasses[i].second, &grasses[i].first);
        costs[i+N] = grasses[i].second;
    }
    sort(costs, costs+N+M);
    costs_end = unique(costs, costs+N+M);

    sort(cows, cows+N);
    reverse(cows, cows+N);
    sort(grasses, grasses+M);
    reverse(grasses, grasses+M);

    LL ans = 0;
    int grass_pos = 0;
    TIMES(i, N) {
        while(grass_pos < M && grasses[grass_pos].first >= cows[i].first) {
            bit.add(get(grasses[grass_pos].second), 1);
            ++grass_pos;
        }
        int lowest = bit.find_min(get(cows[i].second));
        if(bit.read_single(lowest) > 0) {
            //printf("%d\n", cost_dict_rev[lowest]);
            ans += costs[lowest-1];
            bit.add(lowest, -1);
        } else {
            ans = -1;
            break;
        }
    }
    printf("%lld\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
