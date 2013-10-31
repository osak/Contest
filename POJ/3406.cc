//Name: Last digit
//Level: 2
//Category: 数学,Math,素因数分解
//Note:

/**
 * 1からNまでの数の素因数分解をO(log N)くらいで求められるようにしておけば、
 * 素因数の個数を数えながら定義式通りに計算し、last nonzero digitを求められる。
 *
 *オーダーはO(N log N)。
 */
#include <cstdio>
#include <algorithm>

using namespace std;

bool is_prime[1000001];
int min_factor[1000001];
int factors[1000001];

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    fill_n(is_prime, N+1, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i <= N; ++i) {
        if(is_prime[i]) {
            min_factor[i] = i;
            for(long long j = static_cast<long long>(i)*i; j <= N; j += i) {
                is_prime[j] = false;
                if(min_factor[j] == 0) min_factor[j] = i;
            }
        }
    }

    for(int i = 0; i < M; ++i) {
        {
            int tmp = N-i;
            while(tmp > 1) {
                factors[min_factor[tmp]]++;
                tmp /= min_factor[tmp];
            }
        }
        {
            int tmp = i+1;
            while(tmp > 1) {
                factors[min_factor[tmp]]--;
                tmp /= min_factor[tmp];
            }
        }
    }
    int tens = min(factors[2], factors[5]);
    factors[2] -= tens;
    factors[5] -= tens;
    int res = 1;
    for(int i = 2; i <= N; ++i) {
        for(int j = 0; j < factors[i]; ++j) {
            res *= i;
            res %= 10;
        }
    }
    printf("%d\n", res);
    return 0;
}
