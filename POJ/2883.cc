//Name: Points
//Level: 3
//Category: グラフ,Graph,DAG,DAG判定
//Note:

/*
 * 関係式はXとYに分離できる．
 * Xについては，点aと点bが
 * ・a.x < b.x
 * ・a.x = b.x
 * ・a.x > b.x
 * のどれであるかが関係式から求められる．
 * これが実現可能であるかどうかは，与えられた関係式が半順序であるか，すなわち
 * =で結ばれているノードを同一視したとき，DAGを構成しているかを確かめれば良い．
 * Yについても同様．
 *
 * DAGかどうかをDFSで確かめるするときには，既に判定したノードはその先がDAGだと分かっているので飛ばせる．
 *
 * オーダーは O(NM)．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)

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

inline int dir2idx(const string &str) {
    if(str == "N") return 0;
    else if(str == "E") return 1;
    else if(str == "S") return 2;
    else if(str == "W") return 3;
    else if(str == "NE") return 4;
    else if(str == "NW") return 5;
    else if(str == "SE") return 6;
    else if(str == "SW") return 7;
    else {
        cerr << str << endl;
        assert(false);
    }
}

//dir = 0 : x
//      1 : y
int relarr[2][8] = {
    {0, -1, 0, 1, -1, 1, -1, 1},
    {-1, 0, 1, 0, -1, -1, 1, 1}
};

struct Relation {
    int a, rel, b;
    Relation(int a, int rel, int b) : a(a), rel(rel), b(b) {}
};

enum NodeState {
    NONE, DAG, VISITED
};
bool dfs(int pos, const vector<set<int> > &graph, vector<NodeState> &visited) {
    visited[pos] = VISITED;
    FOREACH(it, graph[pos]) {
        if(visited[*it] == VISITED) return false;
        if(visited[*it] == DAG) continue;
        if(!dfs(*it, graph, visited)) return false;
    }
    return true;
}

bool check(const vector<Relation> &relations, int N, int dir) {
    DisjointSet ds(N);
    FOREACH(it, relations) {
        if(relarr[dir][it->rel] == 0) {
            ds.unite(it->a, it->b);
        }
    }

    vector<set<int> > graph(N);
    FOREACH(it, relations) {
        const int a = ds.root(it->a);
        const int b = ds.root(it->b);
        if(relarr[dir][it->rel] == 1) {
            graph[b].insert(a);
        } else if(relarr[dir][it->rel] == -1) {
            graph[a].insert(b);
        }
    }

    vector<NodeState> visited(N, NONE);
    for(int i = 0; i < N; ++i) {
        if(!visited[i] == DAG) {
            if(!dfs(i, graph, visited)) return false;
            FOREACH(it, visited) {
                if(*it == VISITED) *it = DAG;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while(T--) {
        int N, M;
        cin >> N >> M;
        vector<Relation> relations;
        for(int i = 0; i < M; ++i) {
            int a, b;
            string rel;
            cin >> a >> rel >> b;
            --a; --b;
            relations.push_back(Relation(a, dir2idx(rel), b));
        }

        if(check(relations, N, 0) && check(relations, N, 1)) cout << "POSSIBLE" << endl;
        else cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}
