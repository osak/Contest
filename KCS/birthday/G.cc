#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long LL;

const int LIM = 10000000;
bool is_prime[LIM+1];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    fill_n(is_prime, LIM+1, true);
    vector<LL> primes;
    is_prime[0] = is_prime[1] = false;
    primes.push_back(2);
    for(int i = 4; i <= LIM; i += 2) {
        is_prime[i] = false;
    }
    for(int i = 3; i <= LIM; i += 2) {
        if(is_prime[i]) {
            primes.push_back(i);
            for(LL j = (LL)i * i; j <= LIM; j += i) {
                is_prime[j] = false;
            }
        }
    }

    LL S, W, H;
    cin >> S >> H >> W;
    vector<bool> res(H*W, true);
    const LL U = S + H*W - 1;
    for(LL p : primes) {
        if(p > U) break;
        LL start;
        if(p > S) start = p*p;
        else if(S % p == 0) start = S;
        else start = p * ((S + p) / p);
        for(LL i = start; i <= U; i += p) {
            if(i != p) res[i-S] = false;
        }
    }
    if(S == 1) res[0] = false;

    for(int r = 0; r < H; ++r) {
        for(int c = 0; c < W; ++c) {
            if(c > 0) cout << " ";
            if(res[r*W+c]) cout << "Y";
            else cout << "N";
        }
        cout << endl;
    }
    return 0;
}
