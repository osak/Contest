#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<bool> is_prime(3001, true);
    vector<int> primes;

    primes.push_back(2);
    for(int i = 3; i < 3001; i += 2) {
        if(is_prime[i]) {
            for(int j = i*2; j < 3001; j += i) {
                is_prime[j] = false;
            }
            primes.push_back(i);
        }
    }

    int N;
    cin >> N;

    int cnt = 0;
    for(int i = 1; i <= N; ++i) {
        int pcnt = 0;
        int num = i;
        for(int j = 0; j < primes.size(); ++j) {
            if(primes[j] > num) break;
            if(num % primes[j] == 0) {
                while(num % primes[j] == 0) num /= primes[j];
                if(++pcnt > 2) break;
            }
        }
        if(pcnt == 2) ++cnt;
    }

    cout << cnt << endl;
    return 0;
}
