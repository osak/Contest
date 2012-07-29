#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <utility>

using namespace std;

int dp[32][32][32][32];
int best[32][32][32][32];
int visited[32][32][32][32];
int integral[32][32];
int H, W, S;
int ALL_VAL;

inline void sel_max(int &ref, int val) {
  if(ref < val) ref = val;
}

inline int get_integral(int r, int c) {
  if(r < 0 || H <= r || c < 0 || W <= c) return 0;
  return integral[r][c];
}

inline int get_integral_region(int top, int left, int bottom, int right) {
  int val = get_integral(bottom,right) 
          - get_integral(bottom,left-1)
          - get_integral(top-1, right)
          + get_integral(top-1, left-1);
  return val;
}

inline int isok(int top, int left, int bottom, int right) {
 return get_integral_region(top, left, bottom, right) >= get_integral(H-1, W-1) - S;
}


pair<int,int> rec(int top, int left, int bottom, int right) {
  if(visited[top][left][bottom][right]) return make_pair(dp[top][left][bottom][right], best[top][left][bottom][right]);

  //assume args are valid(isok returns true)
  dp[top][left][bottom][right] = 1;
  best[top][left][bottom][right] = get_integral_region(top, left, bottom, right);
  for(int tb = top; tb < bottom; ++tb) {
    if(!isok(top, left, tb, right) || !isok(tb+1, left, bottom, right)) continue;

    const pair<int,int> res1 = rec(top, left, tb, right);
    const pair<int,int> res2 = rec(tb+1, left, bottom, right);
    int ngroups = res1.first + res2.first;
    int yojo = min(res1.second, res2.second);
    if(ngroups == dp[top][left][bottom][right]) {
      sel_max(best[top][left][bottom][right], yojo);
    }
    else if(ngroups > dp[top][left][bottom][right]) {
      dp[top][left][bottom][right] = ngroups;
      best[top][left][bottom][right] = yojo;
    }
  }
  //copype 
  for(int lr = left; lr < right; ++lr) {
    if(!isok(top, left, bottom, lr) || !isok(top, lr+1, bottom, right)) continue;

    const pair<int,int> res1 = rec(top, left, bottom, lr);
    const pair<int,int> res2 = rec(top, lr+1, bottom, right);
    int ngroups = res1.first + res2.first;
    int yojo = min(res1.second, res2.second);
    if(ngroups == dp[top][left][bottom][right]) {
      sel_max(best[top][left][bottom][right], yojo);
    }
    else if(ngroups > dp[top][left][bottom][right]) {
      dp[top][left][bottom][right] = ngroups;
      best[top][left][bottom][right] = yojo;
    }
  }

  visited[top][left][bottom][right] = 1;
  return make_pair(dp[top][left][bottom][right], best[top][left][bottom][right]);
}

int main() {
  ios::sync_with_stdio(0);

  while(true) {
    cin >> H >> W >> S;
    if(!H && !W && !S) break;

    vector<vector<int> > u(H, vector<int>(W));
    for(int r = 0; r < H; ++r) {
      for(int c = 0; c < W; ++c) {
        cin >> u[r][c];
      }
    }

    memset(dp, 0, sizeof(dp));
    memset(best, 0, sizeof(best));
    memset(visited, 0, sizeof(best));
    memset(integral, 0, sizeof(integral));

    integral[0][0] = u[0][0];
    for(int r = 0; r < H; ++r) {
      for(int c = 0; c < W; ++c) {
        int pr = r-1 >= 0 ? integral[r-1][c] : 0;
        int pc = c-1 >= 0 ? integral[r][c-1] : 0;
        int prpc = (r-1>=0 && c-1>=0) ? integral[r-1][c-1] : 0;
        integral[r][c] = pr + pc - prpc + u[r][c];
      }
    }

    ALL_VAL = get_integral_region(0, 0, H-1, W-1);
    const pair<int,int> ans = rec(0, 0, H-1, W-1);
    cout << ans.first << ' ' << ans.second - (ALL_VAL - S)  << endl;
  }
}

