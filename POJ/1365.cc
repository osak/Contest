//Name: Prime Land
//Level: 2
//Category: 素数,素因数分解
//Note: 入力は(素数,指数)の組

/*
 * 素因数分解された数値を読み込み，1引いて素因数分解するだけ．
 * 入力が分かりにくい．
 *
 * オーダーは素因数分解が O(log N) 程度．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <bitset>

using namespace std;

const int LIM = 32768;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    bitset<LIM> is_prime;
    vector<int> primes;
    is_prime.set();
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i < LIM; ++i) {
        if(is_prime[i]) {
            primes.push_back(i);
            for(int j = i*i; j < LIM; j+= i) is_prime[j] = false;
        }
    }
    while(true) {
        string line;
        getline(cin, line);
        if(line == "0") break;

        istringstream is(line);
        int val = 1;
        while(!is.eof()) {
            int p, n;
            is >> p >> n;
            while(n--) val *= p;
        }
        --val;
        bool first = true;
        for(vector<int>::const_reverse_iterator it = primes.rbegin(); it != primes.rend(); ++it) {
            int cnt = 0;
            while(val % *it == 0) {
                ++cnt;
                val /= *it;
            }
            if(cnt > 0) {
                if(!first) cout << ' ';
                cout << *it << ' ' << cnt;
                first = false;
            }
        }
        cout << endl;
    }
    return 0;
}
