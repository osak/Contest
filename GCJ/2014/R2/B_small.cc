#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef long long LL;
const LL MOD = 1000000007;
const LL INF = 10000000000LL;

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

int bubble_cnt(const vector<pair<LL,int>> &v, int start, int end) {
    BIT<int> bit(2000);
    int res = 0;
    for(int i = start; i < end; ++i) {
        const int val = 1500 - v[i].second;
        res += bit.read(val);
        bit.add(val, 1);
    }
    return res;
}

void solve(int CASE) {
    int N;
    cin >> N;

    vector<LL> as(N);
    map<LL,LL> dict;
    for(int i = 0; i < N; ++i) {
        cin >> as[i];
        dict[as[i]] = 1;
    }
    {
        int idx = 1;
        for(auto &p : dict) {
            p.second = idx;
            ++idx;
        }
    }
    vector<pair<LL,int>> pas;
    for(int i = 0; i < N; ++i) {
        pas.push_back(make_pair(as[i], i+1));
    }

    LL res = INF;
    for(int pat = 0; pat < (1<<N); ++pat) {
        vector<pair<LL,int>> pre, post;
        for(int i = 0; i < N; ++i) {
            if(pat & (1<<i)) pre.push_back(pas[i]);
            else post.push_back(pas[i]);
        }
        sort(pre.begin(), pre.end());
        sort(post.begin(), post.end());
        reverse(post.begin(), post.end());
        auto v = pre;
        v.insert(v.end(), post.begin(), post.end());
        const int cost = bubble_cnt(v, 0, N);
        //cout << cost << endl;
        if(cost <= res) {
            res = cost;
            for(int i = 0; i < N; ++i) {
                cout << "(" << v[i].first << " " << v[i].second << ")";
            }
            cout << endl;
        }
    }
    cout << "Case #" << CASE << ": " << res << endl;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    for(int CASE = 1; CASE <= N; ++CASE) {
        solve(CASE);
    }
    return 0;
}
