//Name: Twin Prime
//Level: 2
//Category: 数学,素数
//Note: 

/**
 * 10000以下の双子素数を列挙しておけば、あとは線形探索でよい。
 *
 * オーダーは O(M log log M)。
 * ただしMは求める必要がある最大の素数で、M=10000。
 */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<bool> eratosthenes(int N) {
    vector<bool> is_prime(N+1, true);
    is_prime[0] = is_prime[1] = false;

    const int LIM = static_cast<int>(sqrt(N));
    for(long long i = 2; i <= LIM; ++i) {
        if(is_prime[i]) {
            for(long long j = i*i; j <= N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

bool solve(bool first) {
    const static auto is_prime = eratosthenes(10000);

    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;
    for(int i = N; i >= 0; --i) {
        if(is_prime[i] && is_prime[i-2]) {
            cout << i-2 << ' ' << i << endl;
            break;
        }
    }

    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
