#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long LL;

LL g[1000];
LL sum[1000];
LL doublesum[1000];
int nextpos[1000];
int doublenext[1000];

int main() {
    int T;
    cin >> T;
    for(int cases = 1; cases <= T; cases++) {
        int R, k, N;
        cin >> R >> k >> N;
        memset(g, 0, sizeof(LL)*N);
        memset(sum, 0, sizeof(LL)*N);
        memset(doublesum, 0, sizeof(LL)*N);
        memset(nextpos, 0, sizeof(int)*N);
        memset(doublenext, 0, sizeof(int)*N);
        for(int i = 0; i < N; ++i) {
            cin >> g[i];
        }
        for(int i = 0; i < N; ++i) {
            int j = i;
            while(true) {
                LL tmp = sum[i] + g[j];
                if(tmp > k) break;
                sum[i] = tmp;
                if(++j >= N) j = 0;
                if(j == i) break;
            }
            nextpos[i] = j;
        }

        for(int i = 0; i < N; ++i) {
            doublesum[i] = sum[i] + sum[nextpos[i]];
            doublenext[i] = nextpos[nextpos[i]];
        }

        int pos = 0;
        LL result = 0;
        for(int i = 0; i < R/2; ++i) {
            result += doublesum[pos];
            pos = doublenext[pos];
        }
        if(R % 2 == 1) {
            result += sum[pos];
        }

        printf("Case #%d: %lld\n", cases, result);
    }
}
