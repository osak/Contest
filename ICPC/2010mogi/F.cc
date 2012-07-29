#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cstdio>

using namespace std;

struct Suimon {
    int X,L,F,D,UD;
};

int main() {
    while(true) {
        int N, M, K;
        cin >> N >> M >> K;
        if(!N && !M && !K) break;

        vector<Suimon> suimon(N+1);
        vector<double> suimon_next(N+1, 0);
        vector<int> v(M);

        for(int i = 0; i < N; ++i) {
            Suimon s;
            cin >> s.X >> s.L >> s.F >> s.D >> s.UD;
            suimon[i] = s;
            suimon_next[i] = s.UD ? ((double)s.L/s.F) : 0;
        }
        Suimon last;
        last.X = K;
        last.L = 0;
        last.D = last.F = 1;
        last.UD = 0;
        suimon[N] = last;

        for(int i = 0; i < M; ++i) {
            cin >> v[i];
        }

        double ans = 0;
        int top = 0;
        vector<vector<double> > t(N+1, vector<double>(2, 0));
        vector<double> gtime(M);
        for(int i = 0; i < M; ++i) {
            for(int j = 0; j < N; ++j) {
                int prevx = -i;
                if(j > 0) prevx = suimon[j-1].X;
                double prevt = 0;
                if(j > 0) prevt = t[j-1][1];

                t[j][0] = max(prevt+(double)(suimon[j].X-prevx)/v[i], suimon_next[j]);
                t[j][1] = t[j][0] + (double)suimon[j].L / (suimon[j].UD ? suimon[j].D : suimon[j].F);
                suimon_next[j] = t[j][1] + (double)suimon[j].L / (suimon[j].UD ? suimon[j].F : suimon[j].D);
            }

            double tt = 0;
            for(int j = 0; j < i; ++j) {
                tt = max(tt, gtime[j] + (double)(i-j)/v[j]);
            }
            tt = max(tt, t[N-1][1]+(double)(K-suimon[N-1].X)/v[i]);
            gtime[i] = ans = tt;
        }
        printf("%.10f\n", ans);
    }
    return 0;
}
