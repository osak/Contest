//Name: Wireless Network
//Level: 2
//Category: Union-Find
//Note:

/*
 * あるコンピュータを直したら，そこから距離D以内にあって修理済みのものを全て併合する．
 *
 * オーダーはコマンド数をMとしてO(N^2 + M)．
 * ただし，Union-Findの計算量は定数としている．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <complex>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

typedef complex<int> Point;

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

int main() {
    int N, D;
    scanf("%d %d", &N, &D);
    const int DSQ = D*D;

    vector<Point> points;
    vector<vector<int> > neighbors(N);
    TIMES(i, N) {
        int x, y;
        scanf("%d %d", &x, &y);
        points.push_back(Point(x, y));
        TIMES(j, i) {
            if(norm(points[i] - points[j]) <= DSQ) {
                neighbors[i].push_back(j);
                neighbors[j].push_back(i);
            }
        }
    }
    DisjointSet ds(N);
    vector<unsigned char> repaired(N, 0);
    char cmd;
    while(scanf(" %c", &cmd) != EOF) {
        if(cmd == 'O') {
            int i;
            scanf("%d", &i);
            --i;
            FOREACH(it, neighbors[i]) {
                if(repaired[*it]) ds.unite(i, *it);
            }
            repaired[i] = 1;
        } else if(cmd == 'S') {
            int i, j;
            scanf("%d %d", &i, &j);
            --i; --j;
            if(ds.root(i) == ds.root(j)) cout << "SUCCESS" << endl;
            else cout << "FAIL" << endl;
        }
    }
    return 0;
}
