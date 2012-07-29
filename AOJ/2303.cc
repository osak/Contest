#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

struct Tag {
    double p, t, v;
};

double dp[51][100][51]; // dp[M][N][k] for k rests
double tim[100][51];

int main() {
    int N, M, L;
    cin >> N >> M >> L;

    vector<Tag> v;
    for(int i = 0; i < N; ++i) {
        Tag t;
        cin >> t.p >> t.t >> t.v;
        t.p /= 100;
        v.push_back(t);
    }

    for(int i = 0; i < N; ++i) {
        dp[0][i][0] = 1;
    }
    for(int m = 1; m <= M; ++m) {
        for(int n = 0; n < N; ++n) {
            for(int k = 0; k <= M; ++k) {
                dp[m][n][k] = v[n].p*dp[m-1][n][k-1] + (1-v[n].p)*dp[m-1][n][k];
                //printf("%d %d %d = %d\n", m, n, k, dp[m][n][k]);
            }
        }
    }
    for(int n = 0; n < N; ++n) {
        tim[n][0] = (double)L / v[n].v;
        for(int k = 1; k <= M; ++k) {
            tim[n][k] = tim[n][k-1] + v[n].t;
        }
    }
    for(int n = 0; n < N; ++n) {
        double prob = 0;
        if(v[n].v == 0) goto END;

        for(int k = 0; k <= M; ++k) {
            double tmp = dp[M][n][k];
            for(int nn = 0; nn < N; ++nn) {
                if(n == nn) continue;
                double *bound = upper_bound(tim[nn], tim[nn]+M+1, tim[n][k]);
                int idx = bound - tim[nn];
                double sum = 0;
                for(int i = idx; i <= M; ++i) sum += dp[M][nn][i];
                tmp *= sum;
            }
            prob += tmp;
        }
END:
        printf("%.6f\n", prob);
    }

    return 0;
}
