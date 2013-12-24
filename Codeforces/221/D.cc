//Name: Tree and Queries
//Level: 5
//Category: 木,Tree,動的計画法,DP,データ構造をマージする一般的なテク
//Note:

/**
 * クエリを頂点ごとに分類して、木を深さ優先でたどりながら処理できるように変形する。
 * 各頂点では、基本的には子を全てたどっていき、色の出現数から種類数を引けるようにしたBITを更新させ、
 * 前処理しておいたクエリに答えていく。
 *
 * これをナイーブに実装すると、それぞれの頂点で子を全てたどる操作が発生するため、O(N^2)になる
 * （1列に並んでいる時が最悪ケースである）。
 * ただし、木を上から処理していく関係上、子の処理を先に行うことにすると、1つだけたどり直さなくてよい子を
 * 作ることができる。
 * 最もサイズの大きい子をこのような子として選ぶことで、全体がO(N log N)になる。
 * これは、データ構造をマージする一般的なテクと呼ばれている。
 *   http://iwi.tc/talks/contests/joi_building2.pdf
 *
 * 証明は以下のようにしてできる。
 * 現在見ている頂点をvとして、サイズsiの部分木ciがこのような子として選ばれなかったとき、
 * vはciより大きな子をもっている。
 * したがって、vを根とした部分木のサイズは2✕si以上である。
 * 再帰が巻き戻るにつれてciが再びたどり直されることもあるが、たどり直されたとき、そのときの部分木は
 * 2^(ciがたどり直された回数)✕si以上のサイズをもっていなければならない。
 * なぜなら、ある頂点を根とした部分木がciをたどる時、これがk回目であったとすると、
 * この部分木はciをk-1回目にたどった部分木（これは2^(k-1)✕si以上のサイズをもつ）を子としてもつからである。
 * したがって、部分木のサイズは高々Nであることから、ciは高々log N回しかたどり直されないことがわかる。
 * 同じことが任意の部分木について言える。
 * 特に葉について最大log N回しかたどり直されないことが言えるため、どの頂点もこの回数は超えず、
 * 結局全体でO(N log N)のオーダーになる。
 */
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>

using namespace std;

template <class T>
struct BIT/*{{{*/
{
  vector<T> tree;
  const int size;
  BIT(int s) : tree(s), size(s) {}
  // i 番目までの要素の累積和
  int read(int i) const
  {
    if(i == 0) return 0;
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
    if(i == 0) return;
    while (i <= size) {
      tree[i] += v;
      i += (i & -i);
    }
  }

  void clear() {
      fill(tree.begin(), tree.end(), 0);
  }
};/*}}}*/

const int MAX = 100000;
vector<int> color_of;
vector<vector<int>> children_of;
vector<vector<pair<int,int>>> query_of;
vector<int> ans;
vector<int> size_of;
int color_cnt[MAX+1];
BIT<int> bit(MAX+1);

int build_tree(int v, int parent) {
    size_of[v] = 1;
    int parent_idx = -1;
    int idx = 0;
    for(int child : children_of[v]) {
        if(child == parent) {
            parent_idx = idx;
        } else {
            size_of[v] += build_tree(child, v);
        }
        ++idx;
    }
    if(parent_idx != -1) children_of[v].erase(children_of[v].begin()+parent_idx);
    return size_of[v];
}

void add(int v, int d) {
    bit.add(color_cnt[color_of[v]], -1);
    color_cnt[color_of[v]] += d;
    bit.add(color_cnt[color_of[v]], 1);
    for(int child : children_of[v]) {
        add(child, d);
    }
}

void calc(int v) {
    if(size_of[v] > 1) {
        int largest = -1;
        int largest_idx = -1;
        for(int child : children_of[v]) {
            if(size_of[child] > largest) {
                largest = size_of[child];
                largest_idx = child;
            }
        }
        for(int child : children_of[v]) {
            if(child != largest_idx) {
                calc(child);
                add(child, -1);
            }
        }
        calc(largest_idx);
        for(int child : children_of[v]) {
            if(child != largest_idx) add(child, 1);
        }
    }
    bit.add(color_cnt[color_of[v]], -1);
    color_cnt[color_of[v]]++;
    bit.add(color_cnt[color_of[v]], 1);
    /*
    cout << v << ' ' << bit.read(MAX) << ' ';
    for(int i = 1; i <= 3; ++i) {
        cout << bit.read_single(i) << ' ';
    }
    cout << endl;
    */
    for(auto &q : query_of[v]) {
        ans[q.first] = bit.read(MAX) - bit.read(q.second-1);
    }
}

bool solve() {
    int N, M;
    if(!(cin >> N >> M)) return false;
    if(!N && !M) return false;

    color_of.resize(N+1);
    children_of.resize(N+1);
    query_of.resize(N+1);
    size_of.resize(N+1);
    fill_n(color_cnt, MAX+1, 0);
    for(int i = 0; i < N; ++i) {
        cin >> color_of[i+1];
        children_of[i+1].clear();
        query_of[i+1].clear();
    }
    for(int i = 0; i < N-1; ++i) {
        int a, b;
        cin >> a >> b;
        children_of[a].push_back(b);
        children_of[b].push_back(a);
    }
    for(int i = 0; i < M; ++i) {
        int v, k;
        cin >> v >> k;
        query_of[v].push_back(make_pair(i, k));
    }
    ans.resize(M);
    build_tree(1, -1);
    bit.clear();
    calc(1);
    for(int i : ans) {
        cout << i << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
