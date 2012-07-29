//Name: Prime Number II
//Level: 1
//Category: 素数,探索,upper_bound,lower_bound
//Note:

/*
 * 50000より大きい最初の素数までを列挙し、lower_boundとupper_boundで探索すればよい。
 * lower_boundは初めてx>=nとなるxの場所を返し、upper_boundは初めてn<xとなるxの場所を返すことに注意。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    vector<int> primes;
    vector<int> is_prime(60001, 1);
    is_prime[0] = is_prime[1] = 0;
    int lim = (int)sqrt(60000);
    for(int i = 2; i <= lim; ++i) {
        if(is_prime[i]) {
            if(i <= lim) {
                for(int j = i*i; j <= 60000; j += i) is_prime[j] = 0;
            }
        }
    }
    for(int i = 2; i <= 60000; ++i) 
        if(is_prime[i]) primes.push_back(i);

    int n;
    while(cin >> n) {
        cout << *(lower_bound(primes.begin(), primes.end(), n)-1) << ' ' << *upper_bound(primes.begin(), primes.end(), n) << endl;
    }
    return 0;
}
