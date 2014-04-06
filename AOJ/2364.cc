//Name: Lucky Dip
//Level: 2
//Category: Union Find
//Note:

/**
 * マスどうしの連結情報をUnion Findで管理する。
 * 初期状態で空きマスどうしをuniteしておき、壁を消すクエリがくるたびに
 * その壁のあったマスと4近傍をuniteする。
 *
 * 壁と空きマスをuniteしてはいけないことに注意。
 *
 * オーダーはO(WH + N)。
 */
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define TIMES(i_, n_) for(int i_ = 0; i_ < (n_); ++i_)

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
    int W, H;
    if(!(cin >> W >> H)) return false;
    if(!W && !H) return false;

    vector<string> field(H);
    int goal_id = 0;
    TIMES(i, H) {
        cin >> field[i];
        TIMES(j, W) {
            if(field[i][j] == 't') {
                goal_id = i*W + j;
            }
        }
    }

    static const int DR[] = {0, -1, 0, 1};
    static const int DC[] = {1, 0, -1, 0};
    DisjointSet ds(W*H);
    TIMES(r, H) {
        TIMES(c, W) {
            const int cur = r*W + c;
            if(field[r][c] != '#') {
                TIMES(dir, 4) {
                    const int nr = r + DR[dir];
                    const int nc = c + DC[dir];
                    if(nr < 0 || nr >= H || nc < 0 || nc >= W) continue;
                    if(field[nr][nc] == '#') continue;
                    ds.unite(cur, nr*W + nc);
                }
            }
        }
    }
    int K;
    cin >> K;
    vector<int> query;
    TIMES(_, K) {
        int c, r;
        cin >> c >> r;
        query.push_back(r*W + c);
    }
    if(ds.root(0) == ds.root(goal_id)) {
        cout << 0 << endl;
        return true;
    }
    TIMES(i, K) {
        const int cur = query[i];
        const int r = cur / W;
        const int c = cur % W;
        TIMES(dir, 4) {
            const int nr = r + DR[dir];
            const int nc = c + DC[dir];
            if(nr < 0 || nr >= H || nc < 0 || nc >= W) continue;
            if(field[nr][nc] == '#') continue;
            ds.unite(cur, nr*W + nc);
        }
        field[r][c] = '.';
        if(ds.root(0) == ds.root(goal_id)) {
            cout << i+1 << endl;
            return true;
        }
    }
    cout << -1 << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
