#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int SIZE = (1<<15)+1;

int main() {
    bool *is_prime = new bool[SIZE];
    fill(is_prime, is_prime+SIZE, 1);
    is_prime[0] = is_prime[1] = false;

    vector<int> primes;
    for(int i = 2; i < SIZE; ++i) {
        if(is_prime[i]) {
            primes.push_back(i);
            for(int j = i*i; j < SIZE; j += i) is_prime[j] = false;
        }
    }

    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        int cnt = 0;
        for(int i = 0; i < primes.size(); ++i) {
            if(primes[i] > N/2) break;
            if(is_prime[N-primes[i]]) ++cnt;
        }
        cout << cnt << endl;
    }

    return 0;
}
