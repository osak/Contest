// Name: Chebyshev's Theorem
// Level: 1
// Category: 素数
// Note:

/*
 * やるだけ．
 */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 123456*2;
bool is_prime[MAXN+1];

int main() {
    int lim = (int)sqrt(MAXN);

    for(int i = 0; i <= MAXN; ++i) is_prime[i] = true;
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i <= MAXN; ++i) {
        if(is_prime[i]) {
            if(i < lim) {
                for(int j = i*i; j <= MAXN; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }

    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        int cnt = 0;
        for(int i = N+1; i <= N*2; ++i) {
            if(is_prime[i]) ++cnt;
        }
        cout << cnt << endl;
    }

    return 0;
}
