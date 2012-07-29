//Name: Goldbach's Conjecture
//Level: 1
//Category: 素数,やるだけ
//Note:

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    vector<int> primes;
    vector<int> is_prime(50001, 1);
    is_prime[0] = is_prime[1] = 0;
    int lim = (int)sqrt(50000);
    for(int i = 2; i <= lim; ++i) {
        if(is_prime[i]) {
            if(i <= lim) {
                for(int j = i*i; j <= 50000; j += i) is_prime[j] = 0;
            }
        }
    }
    for(int i = 2; i <= 50000; ++i) 
        if(is_prime[i]) primes.push_back(i);

    while(true) {
        int n;
        cin >> n;
        if(!n) break;

        int cnt = 0;
        for(int i = 0; i < primes.size() && primes[i] <= n/2; ++i) 
            if(is_prime[n-primes[i]]) ++cnt;
        cout << cnt << endl;
    }
    return 0;
}
