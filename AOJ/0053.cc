//Name: Sum of Prime Numbers
//Level: 1
//Category: 素数
//Note:

/*
 * 素数の上限値200000は適当。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    vector<int> primes;
    vector<int> is_prime(200001, 1);
    is_prime[0] = is_prime[1] = 0;
    int lim = (int)sqrt(200000);
    for(int i = 2; i <= lim; ++i) {
        if(is_prime[i]) {
            if(i <= lim) {
                for(int j = i*i; j <= 200000; j += i) is_prime[j] = 0;
            }
        }
    }
    for(int i = 2; i <= 200000; ++i) 
        if(is_prime[i]) primes.push_back(i);

    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        int sum = 0;
        for(int i = 0; i < N; ++i) sum += primes[i];
        cout << sum << endl;
    }
    return 0;
}
