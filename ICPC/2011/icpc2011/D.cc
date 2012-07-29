#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>
#include <queue>

using namespace std;

typedef complex<int> Point;

struct Circle {
  Point center;
  int r;
  int color;

  Circle() {}
  Circle(const Point &c, int r, int clr) : center(c), r(r), color(clr) {}

  bool intersect(const Circle &other) const {
    return norm(center - other.center) < (r+other.r)*(r+other.r);
  }

};

int main() {
  while(true) {
    int N;
    cin >> N;
    if(!N) break;

    vector<vector<int> > on(N);
    vector<int> refered(N, 0);
    vector<Circle> chips;
    for(int i = 0; i < N; ++i) {
      int x, y, r, c;
      cin >> x >> y >> r >> c;
      --c;
      Circle chip(Point(x, y), r, c);
      for(int j = 0; j < i; ++j) {
        if(chips[j].intersect(chip)) {
          on[j].push_back(i);
          refered[i]++;
        }
      }
      chips.push_back(chip);
    }

    vector<int> memo(1<<24, -1);
    priority_queue<pair<int,int> > q;
    q.push(make_pair((1<<N)-1, 0));

    int ans = 0;
    while(!q.empty()) {
      const int state = q.top().first;
      const int num = q.top().second;

      q.pop();

      if(memo[state] != -1) continue;
      memo[state] = num;
      ans = max(ans, num);

      vector<int> ref_buf = refered;
      vector<vector<int> > enabled(4);
      for(int s = state, idx = 0; s; s >>= 1, ++idx) {
        const int b = s&1;
        if(b == 0) {
          for(int i = 0; i < on[idx].size(); ++i) {
            int to = on[idx][i];
            --ref_buf[to];
          }
        }
      }

      for(int i = 0; i < N; ++i) {
        if(ref_buf[i] == 0 && (state&(1<<i))) {
          const Circle &c = chips[i];
          enabled[c.color].push_back(i);
        }
      }

      for(int i = 0; i < enabled.size(); ++i) {
        const vector<int> &v = enabled[i];
        if(v.size() < 2) continue;

        vector<int> chk(v.size(), 0);
        chk[0] = chk[1] = 1;
        reverse(chk.begin(), chk.end());
        do {
          vector<int> sel;
          for(int i = 0; i < chk.size(); ++i) 
            if(chk[i]) sel.push_back(v[i]);

          int ns = state & ~((1<<sel[0]) | (1<<sel[1]));
          if(memo[ns] < num+2) q.push(make_pair(ns, num+2));
        } while(next_permutation(chk.begin(), chk.end()));
      }
    }

    cout << ans << endl;
  }
  return 0;
}
