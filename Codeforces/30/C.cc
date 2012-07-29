#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <cstdio>

using namespace std;

struct Target {
    int x, y, t;
    double e;
    Target() {}
    Target(int xx, int yy, int tt, int ee) : x(xx), y(yy), t(tt), e(ee) {}

    bool operator < (const Target &other) const {
        return t < other.t;
    }
};

int main() {
    int N;
    cin >> N;
    
    vector<Target> targets;
    vector<vector<bool> > canmove(N, vector<bool>(N, false));
    vector<bool> start(N, true);

    for(int i = 0; i < N; ++i) {
        Target t;
        cin >> t.x >> t.y >> t.t >> t.e;
        targets.push_back(t);
    }
    sort(targets.begin(), targets.end());

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if(i == j) continue;
            if(targets[i].t < targets[j].t) continue;

            int dist2 = pow(targets[i].x-targets[j].x, 2) + pow(targets[i].y-targets[j].y, 2);
            if(dist2 <= pow(targets[i].t-targets[j].t, 2)) {
                canmove[j][i] = true;
                start[i] = false;
            }
        }
    }

    vector<double> dp(N, 0);
    for(int i = 0; i < N; ++i) {
        dp[i] = targets[i].e;
    }
    for(int i = 0; i < N; ++i) {
        for(int j = i; j < N; ++j) {
            if(canmove[i][j]) {
                dp[j] = max(dp[j], dp[i]+targets[j].e);
            }
        }
    }
    printf("%.6f\n", *max_element(dp.begin(), dp.end()));

    return 0;
}
