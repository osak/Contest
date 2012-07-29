#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

double distof(const vector<double> &v1, const vector<double> &v2) {
    double ans = 0;
    for(int i = 0; i < 3; ++i) ans += pow(v1[i]-v2[i], 2);
    return ans;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<double> > v(N);
    for(int i = 0; i < N; ++i) {
        v[i].resize(3);
        for(int j = 0; j < 3; ++j) {
            cin >> v[i][j];
        }
    }

    vector<vector<double> > dist(N, vector<double>(N, 0));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < i; ++j) {
            dist[i][j] = dist[j][i] = distof(v[i], v[j]);
        }
    }

    double ans = 0;
    for(int pat = 0; pat < (1<<N); ++pat) {
        if(__builtin_popcount(pat) != M) continue;

        double tmpcnt = 0;
        vector<int> vs;
        for(int i = 0; i < N; ++i) {
            if(pat & (1<<i)) vs.push_back(i);
        }
        for(int i = 0; i < M; ++i) {
            for(int j = 0; j < i; ++j) {
                tmpcnt += dist[vs[i]][vs[j]];
            }
        }
        ans = max(ans, tmpcnt);
    }

    printf("%.6f\n", ans);
    return 0;
}
