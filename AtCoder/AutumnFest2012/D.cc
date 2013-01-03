#include <iostream>
#include <algorithm>
#include <cmath>

typedef unsigned long long ULL;

ULL modpow(ULL a, ULL x, ULL mod) {
    if(x == 0) return 1;
    if(x == 1) return a;
    ULL half = modpow(a, x/2, mod);
    ULL rem = (x&1) ? a : 1;
    return (half*half % mod) * rem % mod;
}


