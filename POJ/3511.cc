//Name: Fermat's Christmas Theorem
//Level: 2
//Category: 素数,二分探索
//Note:

/**
 * 素数のリストと平方和で表せる素数のリストを作り、それぞれの上で二分探索するだけ。
 * 2が平方和で表せることに注意。
 *
 * オーダーはO(N log N)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

const int MAX = 1000000;
bool is_prime[MAX+1];
vector<int> primes, sq_primes;

void init() {
    fill_n(is_prime, MAX+1, true);
    is_prime[0] = is_prime[1] = false;
    sq_primes.push_back(2);
    for(int i = 2; i <= MAX; ++i) {
        if(is_prime[i]) {
            for(long long j = (long long)i*i; j <= MAX; j += i) {
                is_prime[j] = false;
            }
            primes.push_back(i);
            if(i % 4 == 1) sq_primes.push_back(i);
        }
    }
}

bool solve() {
    int L, U;
    scanf("%d %d", &L, &U);
    if(L == -1 && U == -1) return false;
    const int x = lower_bound(primes.begin(), primes.end(), U+1) - lower_bound(primes.begin(), primes.end(), L);
    const int y = lower_bound(sq_primes.begin(), sq_primes.end(), U+1) - lower_bound(sq_primes.begin(), sq_primes.end(), L);
    printf("%d %d %d %d\n", L, U, x, y);
    return true;
}

int main() {
    init();
    while(solve()) ;
    return 0;
}
