// Combination under modulo
// O(N log MOD) for initialization, O(1) for get value.
template<unsigned MOD>
struct ModComb {
    vector<long long> fact;
    vector<long long> inv;

    ModComb(int size) {
        fact.resize(size);
        inv.resize(size);
        fact[0] = 1;
        inv[0] = 1;
        for(int i = 1; i < size; ++i) {
            fact[i] = fact[i-1] * i % MOD;
            inv[i] = 1;
            unsigned x = MOD - 2;
            long long tmp = fact[i];
            while(x > 0) {
                if(x & 1) {
                    inv[i] *= tmp;
                    inv[i] %= MOD;
                }
                tmp *= tmp;
                tmp %= MOD;
                x >>= 1;
            }
        }
    }

    long long get(int n, int m) const {
        return (fact[n] * inv[m] % MOD) * inv[n-m] % MOD;
    }
};
// Not tested
