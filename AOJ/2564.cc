//Name: Tree Reconstruction
//Level: 3
//Category: グラフ,Graph,考察
//Note:

/**
 * まず、入次数と出次数がともに1の頂点は、単なる辺と変わらないので取り除いてよい。
 * この操作をしたあとのグラフで考えると、ある辺eが復元可能な条件は
 * ・eが出ている頂点について、e以外の辺の容量がすべて判明している
 * ・eが入っていく頂点について、e以外の辺の容量がすべて判明している
 * のどちらか（強連結性により、孤立していなければどの頂点も1以上の入次数、出次数をもつため、必ず復元に寄与できる）。
 * これを繰り返し適用することで全体が復元できる必要がある。
 *
 * 上記の条件から、1つの頂点につき、高々1つの辺しか復元できないことが分かる。
 * また、復元を開始するためのポイントとして、初期状態で1辺を除いてすべての辺の容量が判明している頂点が少なくとも1つ必要である。
 * したがって、取り除ける辺数は高々V-1個であることが分かる。
 * 実際、このような選び方は、二部マッチングを用いることで求められる
 * （左の頂点集合を辺、右の頂点集合を頂点として、辺の結ぶ2頂点に対して辺を張ればよい）。
 *
 * この問題では、選び方は関係ないので、入次数と出次数がともに1の頂点を取り除いてから残った辺数と頂点数を数えればよい。
 * グラフ全体が連結とは限らないため、各連結成分ごとにカウントする必要があることに注意が必要だが、連結成分ごとに(頂点数-1)個の辺を除去できるので、
 * 連結成分の個数だけ数えて後からまとめて引けばよい。
 * オーダーは O(N+M)。
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

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

bool solve() {
    int N, M;
    if(!(cin >> N >> M)) return false;
    if(!N && !M) return false;

    int vs = N, es = M;
    DisjointSet ds(N);
    vector<int> in(N, 0), out(N, 0);
    for(int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        out[a]++;
        in[b]++;
        ds.unite(a, b);
    }
    for(int i = 0; i < N; ++i) {
        if(in[i] == 1 && out[i] == 1) {
            --vs;
            --es;
        }
    }
    int comps = 0;
    for(int i = 0; i < N; ++i) {
        if(ds.root(i) == i) {
            ++comps;
        }
    }
    cout << es - vs + comps << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) ;
    return 0;
}
