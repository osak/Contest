//Name: Occurrence of Digits
//Level: 1
//Category: 数学,Math,やるだけ
//Note:

/**
 * 割り算の筆算をシミュレーションしながら、商に立った数を数えていく。
 *
 * オーダーはO(N^2)。
 */
#include <cstdio>
#include <algorithm>
#include <cassert>

using namespace std;

int digit_cnt[101][10];
bool saw[1000];

int main() {
    for(int n = 2; n <= 100; ++n) {
        fill_n(saw, 1000, false);
        int rem = 10;
        while(rem > 0 && !saw[rem]) {
            saw[rem] = true;
            int div = rem / n;
            //printf("%d %d\n", n, rem);
            assert(div <= 9);
            digit_cnt[n][div]++;
            rem %= n;
            rem *= 10;
        }
    }
    for(int n = 1; n <= 100; ++n) {
        for(int d = 0; d <= 9; ++d) {
            digit_cnt[n][d] += digit_cnt[n-1][d];
        }
    }
    int N, K;
    while(scanf("%d %d", &N, &K) != EOF) {
        printf("%d\n", digit_cnt[N][K]);
    }
    return 0;
}
