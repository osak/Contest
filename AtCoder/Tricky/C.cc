#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstdlib>

typedef long double LD;

void solve() {
    int p, x;
    scanf("%d %d", &p, &x);
    int cnt = 0;
    int ans = -1;
    if(p == 2) {
        long long ans = (1LL << x) - 1;
        printf("%lld\n", ans);
        return;
    }
    if(x == 0) {
        ans = 0;
    } else {
        for(int i = 1; i < p*10000000; ++i) {
            int tmp = i;
            while(tmp % p == 0) {
                ++cnt;
                tmp /= p;
            }
            //printf("%d %d\n", i, cnt);
            if(i - cnt == x) {
                ans = i;
                break;
            }
        }
    }
    printf("%d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        solve();
    }
    return 0;
}
