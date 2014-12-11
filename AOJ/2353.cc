//Name: Four Arithmetic Operations
//Level: 4
//Category: 数学
//Note:

/**
 * 最後の答えが必ず-2^31から2^31の範囲の整数に収まるので、2^32より大きな素数を法とした有限体の上で計算すればよい。
 * 途中で乗算が64bitに収まらない可能性があるので、乗算は自前でビットシフトを使ったものを実装するとよい。
 *
 * オーダーは O(N log P)。
 */
#include <iostream>

using namespace std;

const long long MOD = 8589934609LL; // 2^33 + 17

long long mul(long long a, long long b) {
    long long res = 0;
    while(b) {
        if(b & 1) {
            res += a;
            res %= MOD;
        }
        a *= 2;
        a %= MOD;
        b /= 2;
    }
    return res;
}

long long modpow(long long a, long long x) {
    long long res = 1;
    while(x) {
        if(x & 1) {
            res = mul(res, a);
        }
        a = mul(a, a);
        x /= 2;
    }
    return res;
}

bool solve() {
    int N;
    if(!(cin >> N)) return false;

    long long x = 0;
    for(int i = 0; i < N; ++i) {
        int o;
        long long y;
        cin >> o >> y;
        if(o == 1) {
            x += y;
            x %= MOD;
        } else if(o == 2) {
            x -= y;
            x += MOD;
            x %= MOD;
        } else if(o == 3) {
            x = mul(x, (y + MOD) % MOD);
        } else if(o == 4) {
            x = mul(x, modpow((y + MOD) % MOD, MOD-2));
        }
    }
    if(x >= (1LL<<31)) x -= MOD;
    cout << x << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
