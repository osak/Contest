#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<pair<int,int> > bfs(const vector<vector<int> >& grid)
{
  const int H = grid.size();
  const int W = grid[0].size();
  vector<vector<int> > visited(H, vector<int>(W, 0));
  visited[0][0] = 1;
  queue<pair<int,int> > q;
  q.push(make_pair(0, 0));
  const int A = grid[0][0];
  vector<pair<int,int> > clus;
  while (!q.empty()) {
    const pair<int,int> p = q.front();
    q.pop();
    clus.push_back(p);
    for (int d = 0; d < 4; d++) {
      static const int di[] = {-1, 1, 0, 0};
      static const int dj[] = {0, 0, -1, 1};
      const int i = p.first + di[d];
      const int j = p.second + dj[d];
      if (0 <= i && i < H && 0 <= j && j < W && !visited[i][j] && grid[i][j] == A) {
        visited[i][j] = 1;
        q.push(make_pair(i, j));
      }
    }
  }
  return clus;
}

int ans = 0;

void solve(const vector<vector<int> >& grid, int C, int depth = 0)
{
  if (depth == 5) {
    const vector<pair<int,int> > clus = bfs(grid);
    if (grid[clus[0].first][clus[0].second] == C) {
      ans = max(ans, int(clus.size()));
    }
    return;
  }
  for (int c = 1; c <= 6; c++) {
    if (grid[0][0] == c) {
      continue;
    }
    const vector<pair<int,int> > clus = bfs(grid);
    vector<vector<int> > g(grid);
    for (vector<pair<int,int> >::const_iterator it = clus.begin(); it != clus.end(); ++it) {
      g[it->first][it->second] = c;
    }
    solve(g, C, depth+1);
  }
}

int main()
{
  int H, W, C;
  while (cin >> H >> W >> C && H != 0) {
    vector<vector<int> > grid(H, vector<int>(W));
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
        cin >> grid[i][j];
      }
    }
    ans = 0;
    solve(grid, C);
    cout << ans << endl;
  }
  return 0;
}
