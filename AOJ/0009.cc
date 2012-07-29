#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int MAX = 1000000;
    int lim = sqrt(MAX);
    vector<int> is_prime(MAX, 1);
    is_prime[0] = is_prime[1] = 0;
    for(int i = 2; i < MAX; ++i) {
        if(is_prime[i])
            if(i < lim) 
                for(int j = i*i; j < MAX; j += i) is_prime[j] = 0;
    }

    vector<int> primes;
    for(int i = 0; i < MAX; ++i)
        if(is_prime[i]) primes.push_back(i);

    int n;
    while(cin >> n) 
        cout << upper_bound(primes.begin(), primes.end(), n)-primes.begin() << endl;
    return 0;
}
