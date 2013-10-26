//Name: Bubble Sort
//Level: 4
//Category: 数学,Math
//Note:

/**
 * 問題を変形して、「K手以下でソート済みにできるパターンの数」を求める。
 *
 * まず、ある数を右側に上げていって目的の場所に置くことは1手でできるが、
 * 左側に降ろしていって目的の場所に置くまでには、その位置の差と同じだけの
 * 手数がかかることが容易にわかる。
 * したがって、後者の最大値が、ある数列をソート済みにするまでの最大手数となる。
 *
 * 次に、K手以下でソート済みにできるような数列の構成方法を考える。
 * 簡単のため、数は0からN-1であるとする。
 *
 * 0を置ける場所は、上記の考察から、要素0からKまでの(K+1)箇所である。
 * 同様に、1を置ける場所は、要素0から1+Kまでの(K+2)箇所存在するが、
 * このうちの1箇所にはすでに0が置いてあるため、1も(K+1)箇所に置ける。
 * 同様の考察を繰り返すことで、N-K-1までは(K+1)箇所に置けることがわかる。
 * N-K以降の数は、置ける場所の右端が変化しないため、(N-i)箇所に置ける。
 *
 * これらを合わせて考えると、求めるパターン数は
 *   P'(N, K) = (K+1)^(N-K) * K! = (K+1)^(N-K-1) * (K+1)!
 * となる。
 * あとは、差分
 *   P(N, K) = P'(N, K) - P'(N, K-1)
 * を計算すればよい。
 *
 * オーダーはO(log N)。
 */
#include <cstdio>

using namespace std;

typedef long long LL;

const LL MOD = 20100713;

LL factorial[1000001];

LL modpow(LL a, LL x) {
    LL res = 1;
    LL ord = a;
    while(x) {
        if(x % 2 == 1) {
            res *= ord;
            res %= MOD;
        }
        ord *= ord;
        ord %= MOD;
        x >>= 1;
    }
    return res;
}

int main() {
    factorial[0] = 1;
    for(int i = 1; i <= 1000001; ++i) {
        factorial[i] = factorial[i-1] * i % MOD;
    }
    int T;
    scanf("%d", &T);
    while(T--) {
        int N, K;
        scanf("%d %d", &N, &K);
        const LL pat1 = modpow(K, N-K) * factorial[K] % MOD;
        const LL pat2 = modpow(K+1, N-K-1) * factorial[K+1] % MOD;
        printf("%d\n", static_cast<int>(pat2-pat1+MOD)%MOD);
    }
    return 0;
}
