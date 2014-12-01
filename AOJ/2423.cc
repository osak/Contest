//Name: Code Art Online
//Level: 3
//Category: 幾何,Geometry,最小包含円,マッチング,辞書順最小
//Note:

/*
 * まず、ある図形が穴を通れるかは、図形の最小包含円を求めて、その直径と穴の直径を比較すればよい。
 * 
 * これを元に図形と円の二部グラフができるので、辞書順最小マッチングを求める。
 * 左側のノード1を対応させる右側頂点をひとつ決めて、残りの頂点でマッチングができるなら採用、そうでなければ他の頂点を試す……という操作を繰り返せば良い。
 *
 * オーダーは O(MP log P + (NM)^2)。
 * ただし、辞書順最小マッチングの実際のループ数は(NM)^2回よりずっと少ないはずである。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
#include <numeric>

using namespace std;

typedef complex<double> P;
const double EPS = 1e-9;

pair<P, double> enclosing_circle(const vector<P> &ps) {
    P c = accumulate(begin(ps), end(ps), P(0, 0)) / (double)ps.size();
    for(int i = 0; i < 1000; ++i) {
        P farthest;
        double maxd = 0;
        for(const P &p : ps) {
            double d = abs(c - p);
            if(d > maxd) {
                farthest = p;
                maxd = d;
            }
        }
        P vec = farthest - c;
        c += vec * pow(0.9, i+1);
    }
    double d = 0;
    for(const P &p : ps) {
        d = max(d, abs(p-c));
    }
    return make_pair(c, d);
}

bool bm_augment(const vector<vector<int> >& g, int u, vector<int>& match_to, vector<bool>& visited) // {{{
{
  if (u < 0) {
    return true;
  }

  for (vector<int>::const_iterator it(g[u].begin()); it != g[u].end(); ++it) {
    if (!visited[*it]) {
      visited[*it] = true;
      if (bm_augment(g, match_to[*it], match_to, visited)) {
        match_to[u] = *it;
        match_to[*it] = u;
        return true;
      }
    }
  }
  return false;
} // }}}

bool bipartite_matching(const vector<vector<int> >& g, int S, int L, const vector<bool> &used)  // {{{
{
  const int N = g.size();
  vector<int> match_to(N, -1);
  for (int u = S; u < L; u++) {
      vector<bool> visited = used;
      if(!bm_augment(g, u, match_to, visited)) return false;
  }
  return true;
} // }}}

bool solve() {
    int N, M;
    if(!(cin >> N >> M)) return false;

    vector<double> holes(N);
    for(int i = 0; i < N; ++i) {
        cin >> holes[i];
    }
    vector<double> persons(M, 0);
    for(int i = 0; i < M; ++i) {
        vector<P> vs;
        int Ps;
        cin >> Ps;
        for(int j = 0; j < Ps; ++j) {
            double x, y;
            cin >> x >> y;
            vs.emplace_back(x, y);
        }
        auto c = enclosing_circle(vs);
        persons[i] = c.second;
    }

    vector<vector<int>> g(M + N);
    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < N; ++j) {
            if(persons[i] < holes[j]+EPS) {
                g[i].push_back(M+j);
            }
        }
    }
    vector<int> ans;
    vector<bool> used(M + N, false);
    if(!bipartite_matching(g, 0, M, used)) {
        cout << "NG" << endl;
        return true;
    }
    for(int i = 0; i < M; ++i) {
        for(int to : g[i]) {
            if(used[to]) continue;
            used[to] = true;
            if(bipartite_matching(g, i+1, M, used)) {
                ans.push_back(to+1-M);
                break;
            }
            used[to] = false;
        }
    }
    for(int a : ans) {
        cout << a << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
