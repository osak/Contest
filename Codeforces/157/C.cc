#define _GLIBCXX_DEBUG

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int LIM = 100000;
const int SQRT = 317;
const int MOD = 1000000007;
bool is_prime[LIM+1];
vector<int> primes;

int freq[LIM+1];
int freq_acc[LIM+1];

long long modpow(int a, int x) {
    if(x < 0) return 0;
    if(x == 0) return 1;
    if(x == 1) return a;
    long long half = modpow(a, x/2);
    if(a % 2 == 0) return half*half % MOD;
    return (half*half % MOD) * a % MOD;
}

vector<int> divisor(int n) {
    vector<int> division;
    for(vector<int>::iterator it = primes.begin(); it != primes.end(); ++it) {
        while(n > *it && n % *it == 0) {
            division.push_back(*it);
            n /= *it;
        }
        if(n < *it || is_prime[n]) break;
    }
    if(n > 1) division.push_back(n);

    const int L = division.size();
    vector<int> divisors;
    for(int pat = 0; pat < (1<<L); ++pat) {
        int acc = 1;
        for(int i = 0; i < L; ++i) {
            if(pat & (1<<i)) acc *= division[i];
        }
        divisors.push_back(acc);
    }
    sort(divisors.begin(), divisors.end());
    divisors.erase(unique(divisors.begin(), divisors.end()), divisors.end());
    return divisors;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    fill_n(is_prime, LIM+1, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i <= SQRT; ++i) {
        if(is_prime[i]) {
            primes.push_back(i);
            if(i < SQRT) {
                for(int j = i*i; j <= LIM; j += i) is_prime[j] = false;
            }
        }
    }

    int N;
    cin >> N;
    vector<int> as(N);
    int maxval = 0;
    for(int i = 0; i < N; ++i) {
        cin >> as[i];
        freq[as[i]]++;
        maxval = max(maxval, as[i]);
    }

    for(int i = 1; i <= LIM; ++i) {
        freq_acc[i] = freq_acc[i-1] + freq[i];
    }

    long long ans = 0;
    for(int i = 1; i <= maxval; ++i) {
        vector<int> divisors = divisor(i);
        divisors.push_back(maxval+1);
        vector<int> cnt(divisors.size(), 0);
        long long acc = 1;
        for(int j = 0; j < (int)divisors.size()-1; ++j) {
            int cnt = freq_acc[divisors[j+1]-1] - freq_acc[divisors[j]-1];
            cout << divisors[j] << ' ' << cnt << endl;
            if(divisors[j] == i) --cnt;
            acc *= modpow(j+1, cnt);
        }
        ans += acc;
        ans %= MOD;
    }
    cout << ans << endl;
    return 0;
}
