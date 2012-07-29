#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    vector<bool> is_prime(10000000, true);
    vector<int> primes;

    is_prime[0] = is_prime[1] = false;
    primes.push_back(2);
    int lim = sqrt(10000000);
    for(int i = 4; i < 10000000; i += 2) is_prime[i] = false;
    for(int i = 3; i < 10000000; i += 2) {
        if(is_prime[i]) {
            primes.push_back(i);
            if(i > lim) continue;
            for(int j = i*i; j < 10000000; j += i) {
                is_prime[j] = false;
            }
        }
    }

    printf("int primes[] = {");
    for(int i = 0; i < primes.size(); ++i) {
        printf("%d,", primes[i]);
        if(i % 100 == 0) printf("\n");
    }
    printf("};\n");
    return 0;
}
