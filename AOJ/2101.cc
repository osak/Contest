//Name: Perfect Number
//Level: 2
//Category: 数学,Math,素数,素因数分解
//Note:

/**
 * n = Πp_i^a_i と素因数分解したとき、約数の和は Π_{i <φ(n)} Σ_{0≦j≦a_i} p_i^j となる。
 * オーダーは O(log N)。
 */
#include <iostream>
#include <algorithm>
#include <array>
#include <vector>

using namespace std;

const long long SQMAX = 10000;
array<bool,SQMAX+1> is_prime;
vector<long long> primes;

bool solve() {
    int N;
    cin >> N;
    if(!N) return false;

    int tmp = N;
    long long ans = 1;
    for(long long p : primes) {
        if(p > tmp) break;
        long long s = 1;
        long long fac = 1;
        while(tmp % p == 0) {
            tmp /= p;
            fac *= p;
            s += fac;
        }
        ans *= s;
    }
    if(tmp > 1) {
        ans *= (1 + tmp);
    }
    ans -= N;
    if(ans == N) {
        cout << "perfect number" << endl;
    } else if(ans < N) {
        cout << "deficient number" << endl;
    } else {
        cout << "abundant number" << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    fill(begin(is_prime), end(is_prime), true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i <= SQMAX; ++i) {
        if(is_prime[i]) {
            primes.push_back(i);
            for(long long j = (long long)i*i; j <= SQMAX; j += i) {
                is_prime[j] = false;
            }
        }
    }
    while(solve()) ;
    return 0;
}
