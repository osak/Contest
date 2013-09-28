/*
 * 方程式 x^2 - x - 1 ≡ 0 (mod p)を解き、解が原始根であることを確認する。
 * 素因数分解に篩をつかうと爆速になる。
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <omp.h>

using namespace std;

typedef unsigned long long LL;

const int LIM = 100000000;
const int SQRT = sqrt(LIM);
bool is_prime[LIM+1];
int prime_root[LIM+1];
vector<int> primes;

int negpow(LL n) {
    return (n % 2 == 0) ? 1 : -1;
}

int jacobi(LL a, LL n) {
    if(a == 0) return  ((n == 1) ? 1 : 0);
    if(a % 2 == 1) {
        return negpow((a-1)*(n-1)/4) * jacobi(n%a, a);
    } else {
        return negpow((n*n-1)/8) * jacobi(a/2, n);
    }
}

LL modpow(LL a, LL x, LL mod) {
    LL res = 1;
    LL ord = a % mod;
    while(x > 0) {
        if(x & 1) {
            res *= ord;
            res %= mod;
        }
        ord *= ord;
        ord %= mod;
        x >>= 1;
    }
    return res;
}

LL sqrtMod(LL n, LL p) {
  LL S, Q, W, i, m = modpow(n, p-2, p);
  for (Q = p - 1, S = 0; Q % 2 == 0; Q /= 2, ++S);
  do { W = rand() % p; } while (W == 0 || jacobi(W, p) != -1);
  for (LL R = modpow(n, (Q+1)/2, p), V = modpow(W, Q, p); ;) {
    LL z = (R * R) % p * m % p;
    for (i = 0; i < S && z != 1; z = z*z%p, ++i);
    if (i == 0) return R;
    R = (R * modpow(V, 1 << (S-i-1), p)) % p;
  }
}

/*
LL sqrtMod(LL n, LL p) {
    LL S, Q, Z, i;
    for (Q = p - 1, S = 0; Q % 2 == 0; Q /= 2, ++S);
    //do { Z = rand() % p; } while (Z == 0 || jacobi(Z, p) != -1);
    for(Z = 1; jacobi(Z, p) != -1; ++Z) ;
    assert(jacobi(Z, p) == -1);
    LL t = modpow(n, Q, p);
    LL M = S;
    for (LL R = modpow(n, (Q+1)/2, p), c = modpow(Z, Q, p); ;) {
        if(t == 1) return R;
        i = 0;
        cout << "t m " << t << ' ' << M << endl;
        while(i < M && t != 1) {
            t = t*t % p;
            ++i;
        }
        assert(i < M);
        assert(t == 1);
        LL b = c % p;
        for (LL j = 0; j < M-i-1; ++j) {
            b = b*b % p;
        }
        R = R * b % p;
        t = (t*b % p) * b % p;
        c = b*b % p;
        M = i;
    }
    assert(false);
}
*/

bool is_primitive_root(LL n, LL p) {
    LL tmp = p-1;
    while(tmp > 1) {
        int pr = prime_root[tmp];
        LL gp = modpow(n, (p-1) / pr, p);
        if(gp == 1) return false;
        while(tmp > 1 && prime_root[tmp] == pr) tmp /= pr;
    }
    assert(tmp == 1);
    return true;
}

int main() {
    srand(time(NULL));
    fill_n(is_prime, LIM+1, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i <= LIM; ++i) {
        if(is_prime[i]) {
            prime_root[i] = i;
            for(long long j = (long long)i*i; j <= LIM; j += i) {
                if(is_prime[j]) {
                    prime_root[j] = i;
                    is_prime[j] = false;
                }
            }
            primes.push_back(i);
        }
    }
    LL sum = 0;
    int cnt = 0;
    LL tmp[20] = {0};
    const int N = primes.size();
#pragma omp parallel for
    for(int idx = 0; idx < N; ++idx) {
        const int i = primes[idx];
        if(i == 2) continue;
        //if(i > 10000) break;
        if(idx % 100000 == 0) cout << i << endl;
        LL a = (1 + modpow(4, i-2, i)) % i;
        if(a == 0) {
            if(is_primitive_root(modpow(2, i-2, i), i)) {
                //sum += i;
                //++cnt;
                tmp[omp_get_thread_num()] += i;
            }
        } else if(jacobi(a, i) == 1) {
            //cout << i << ' ' << a << endl;
            LL root = sqrtMod(a, i);
            LL x = (root + modpow(2, i-2, i)) % i;
            LL x2 = (i-root + modpow(2, i-2, i)) % i;
            if(is_primitive_root(x, i) || is_primitive_root(x2, i)) {
                //cout << i << endl;
                //sum += i;
                //++cnt;
                tmp[omp_get_thread_num()] += i;
            }
        }
    }
    for(int i = 0; i < 20; ++i) {
        sum += tmp[i];
    }
    cout << cnt << endl;
    cout << sum << endl;
    return 0;
}
