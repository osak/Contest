//Name: フィボナッチ
//Level: 5
//Cateogry: 数学,漸化式,DP,動的計画法,きたまさ法
//Note: Typical DP Contest T

/**
 * 漸化式を高速に計算するとき、通常は行列の累乗を使うが、この問題では最大で1000*1000の行列を扱うことになり
 * 時間が足りない。
 * O(K^3 log M)より高速に漸化式を求める手法があり、きたまさ法という名前が付いている（らしい）
 *   http://d.hatena.ne.jp/wata_orz/20090922/1253615708
 * 
 * きたまさ法では、ある項 a_m が初項 a_0 .. a_(n-1) を用いて
 *   a_m = ∑b_mj * a_j + b_mn * d
 * と表せるとき、数列全体をmだけずらしても同じ議論が成立することを利用して
 *   a_(2m) = ∑b_mj * a_(m+j) + b_mn * d
 *          = ∑∑b_mj * b_mi * a_(i+j) + (∑b_mj + 1)*b_n*d
 * と式変形を行い、a_(2m)を a_0 .. a_(2n-2) を用いて表す。
 * ここで、a_n .. a_(2n-2)をa_0 .. a_(n-1)で表すのは直接計算しても O(N^2) で間に合う。
 * したがって、この表を用いることで、 a_(2m)を a_0 .. a_(n-1) の組み合わせで表すことができるようになる。
 *
 * この問題では、きたまさ法において d=0 が成立しているため計算しやすくなっている。
 * オーダーは O(K^2 log M)。
 */
#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

const LL MOD = 1000000007;

void add(LL &var, LL val) {
    var = (var + val%MOD) % MOD;
}

int K;
vector<vector<LL>> fact;
vector<LL> dbl(const vector<LL> &v) {
    vector<LL> tmp(K*2, 0);
    for(int i = 0; i < K; ++i) {
        for(int j = 0; j < K; ++j) {
            add(tmp[i+j], v[i]*v[j]);
        }
    }
    for(int i = K; i < K*2; ++i) {
        for(int j = 0; j < K; ++j) {
            add(tmp[j], tmp[i]*fact[i][j]);
        }
    }
    tmp.resize(K);
    return tmp;
}

vector<LL> inc(const vector<LL> &v) {
    vector<LL> tmp(K+1, 0);
    for(int i = 0; i < K; ++i) {
        tmp[i+1] = v[i];
    }
    for(int j = 0; j < K; ++j) {
        add(tmp[j], tmp[K]*fact[K][j]);
    }
    tmp.resize(K);
    return tmp;
}

vector<LL> modpow(const vector<LL> &v, int N) {
    if(N == 1) return v;
    if(N == 2) return inc(v);
    vector<LL> tmp = dbl(modpow(v, N/2));
    if(N % 2 == 1) tmp = inc(tmp);
    return tmp;
}

int main() {
    int N;
    cin >> K >> N;

    fact.resize(K*2);
    // [0, K)
    for(int i = 0; i < K; ++i) {
        fact[i].resize(K, 0);
        fact[i][i] = 1;
    }
    // [K, K+1)
    fact[K].resize(K, 0);
    for(int i = 0; i < K; ++i) {
        fact[K][i] = 1;
    }
    // [K+1, 2K)
    for(int i = K+1; i < 2*K; ++i) {
        fact[i].resize(K, 0);
        for(int j = 0; j < K; ++j) {
            add(fact[i][j], fact[i-1][j]*2);
        }
        for(int j = 0; j < K; ++j) {
            fact[i][j] = (fact[i][j] - fact[i-K-1][j] + MOD) % MOD;
        }
    }

    vector<LL> vec(K, 0);
    vec[1] = 1;
    vec = modpow(vec, N-1);
    LL ans = 0;
    for(LL l : vec) {
        add(ans, l);
    }
    cout << ans << endl;
    return 0;
}
