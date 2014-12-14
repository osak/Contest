//Name: Building a Space Station
//Level: 2
//Category: グラフ,Graph,最小全域木,MST
//Note:

/**
 * 球体と球体を最短距離で結ぶには、中心同士を結ぶような線分で結べばよい。
 * 交差している球の間にはコスト0の辺があるものとして、最小全域木を求めればよい。
 *
 * オーダーは O(N^2 log N)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

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

struct Sphere {
    double x, y, z, r;

    double distance(const Sphere &s) const {
        const double dx = x - s.x;
        const double dy = y - s.y;
        const double dz = z - s.z;
        const double d = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2)) - r - s.r;
        return d < 0 ? 0 : d;
    }
};

struct Edge {
    int a, b;
    double cost;

    Edge(int a, int b, double c) : a(a), b(b), cost(c) {}

    bool operator <(const Edge &e) const {
        return cost < e.cost;
    }
};

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<Sphere> nodes(N);
    for(int i = 0; i < N; ++i) {
        cin >> nodes[i].x >> nodes[i].y >> nodes[i].z >> nodes[i].r;
    }

    vector<Edge> edges;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < i; ++j) {
            edges.emplace_back(i, j, nodes[i].distance(nodes[j]));
        }
    }
    sort(begin(edges), end(edges));

    DisjointSet ds(N);
    double ans = 0;
    for (auto &e : edges) {
        if(ds.unite(e.a, e.b)) {
            ans += e.cost;
        }
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(3);

    while(solve()) ;
    return 0;
}
