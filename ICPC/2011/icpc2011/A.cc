#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
  vector<int> is_prime(123457*2, 1);
  vector<int> primes;
  int lim = sqrt(123457*2);

  is_prime[0] = is_prime[1] = 0;
  for(int i = 2; i < is_prime.size(); ++i) {
    if(is_prime[i]) {
      primes.push_back(i);
      if(i <= lim) {
        for(int j = i*i; j < is_prime.size(); j += i) is_prime[j] = 0;
      }
    }
  }

  while(true) {
    int N;
    cin >> N;
    if(!N) break;

    int cnt = 0;
    for(int i = 0; i < primes.size(); ++i) {
      if(N < primes[i] && primes[i] <= 2*N) ++cnt;
    }
    cout << cnt << endl;

  }
  return 0;
}
