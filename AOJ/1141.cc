//Name: Dirichlet's Theorem on Arithmetic Progressions
//Level: 2
//Category: 数学,Math,素数,練習問題
//Note:

/**
 * 10^6以下の素数を列挙しておき、等差数列を生成しながら素数の個数を数えれば良い。
 *
 * オーダーは O(1/D)？
 */

#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

const int LIM = 1000000;
array<bool,LIM> is_prime;

void init() {
    fill(begin(is_prime), end(is_prime), true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i*i < LIM; ++i) {
        if(is_prime[i]) {
            for(int j = i*i; j < LIM; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

bool solve() {
    int A, D, N;
    if(!(cin >> A >> D >> N)) return false;
    if(!A && !D && !N) return false;

    int cnt = 0;
    int cur = A;
    while(true) {
        if(is_prime[cur]) ++cnt;
        if(cnt == N) {
            cout << cur << endl;
            break;
        }
        cur += D;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    init();
    while(solve()) ;
    return 0;
}
