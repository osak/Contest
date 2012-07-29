#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

const int SIZE = 1000010;

int main() {
    vector<int> is_prime(SIZE, 1);
    is_prime[0] = is_prime[1] = 0;

    vector<int> primes;
    const int lim = sqrt(SIZE);
    for(int i = 2; i < SIZE; ++i) {
        if(is_prime[i]) {
            primes.push_back(i);
            if(i <= lim) {
                for(int j = i*i; j < SIZE; j += i) is_prime[j] = 0;
            }
        }
    }

    long long A;
    int B;
    cin >> A >> B;
    long long LOW = A-B, HIGH = A+B;

    vector<long long> cur(B*2+1);
    vector<int> last_cnt(B*2+1, 10000);
    for(int i = 0; i < B*2+1; ++i) cur[i] = LOW + i;

    for(int i = 0; i < primes.size(); ++i) {
        const int prime = primes[i];
        int offset = 0;
        if(LOW % prime != 0) offset = prime - LOW%prime;

        for(int idx = offset; idx < B*2+1; idx += prime) {
            if(LOW+idx <= 0) continue;
            if(last_cnt[idx] == -1) continue;

            int cnt = 0;
            while(cur[idx] % prime == 0) {
                cur[idx] /= prime;
                ++cnt;
            }
            //cout << prime << ' ' << idx << ' ' << cnt << endl;
            if(last_cnt[idx] < cnt) last_cnt[idx] = -1;
            else last_cnt[idx] = cnt;
        }
    }

    int ans = 0;
    for(int i = 0; i < B*2+1; ++i) {
        if(LOW+i >= 2 && last_cnt[i] != -1) ++ans;
    }

    cout << ans << endl;

    return 0;
}
