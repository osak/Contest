#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>

using namespace std;
const int MAX = 5*1000*1000;

int phi[MAX+1];
unsigned long long accum[MAX+1];
bool is_prime[MAX+1];
vector<int> primes;

int main() {
    ios::sync_with_stdio(0);

    int lim = (int)sqrt(MAX+1);
    fill(is_prime, is_prime+(MAX+1), true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i <= lim; ++i) {
        if(is_prime[i]) {
            primes.push_back(i);
            if(i <= lim) {
                for(int j = i*i; j <= MAX+1; j += i)
                    is_prime[j] = false;
            }
        }
    }

    for(int n = 2; n <= MAX; ++n) {
        int val = 0;
        if(is_prime[n]) {
            val = n;
            int tmp = n;
            for(int i = 0; tmp <= primes[i]; ++i) {
                int p = primes[i];
                if(tmp % p == 0) {
                    val /= p;
                    val *= p-1;
                    while(tmp % p == 0) tmp /= p;
                }
            }
            if(tmp > 1) {
                val /= tmp;
                val *= tmp-1;
            }
        }
        else {
            int lim = (int)sqrt(n);
            for(int i = 0; primes[i] <= lim; ++i) {
                if(n % primes[i] == 0) {
                    int prev = n / primes[i];
                    if(prev % primes[i] != 0) {
                        val = phi[prev] * (primes[i]-1);
                    }
                    else {
                        val = phi[prev] * primes[i];
                    }
                    break;
                }
            }
        }
        phi[n] = val;
        accum[n] += accum[n-1] + (unsigned long long)phi[n]*phi[n];
    }

    int T;
    cin >> T;
    for(int CASE = 1; CASE <= T; ++CASE) {
        int A, B;
        cin >> A >> B;

        unsigned long long ans = accum[B] - accum[A-1];
        cout << "Case " << CASE << ": " << ans << endl;
    }

    return 0;
}
