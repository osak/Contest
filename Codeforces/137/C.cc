//Name: Reducing Fractions
//Level: 3
//Category: 数論,素数,Prime,素因数分解
//Note: Codeforces #137

/*
 * 素因数分解を全てmapに突っこんで約分して再構築……だと，よほどうまくやらないと出力数10^5制限にひっかかる．
 * ちょうど入力が10^5個までなので，入力の数値から公約数を割っていく方法で考える．
 * 数値の上限が小さいので，素因数ごとに分子の何番目の数がそれを持っているかを管理しておき，
 * 分母はひとつずつ素因数分解してこの表から対応するものを消していけばよい．
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int LIM = 3170;
bool is_prime[LIM];
vector<int> primes;
vector<int> table[10000000];

void factoring(int n, map<int,int> &frac, int slug) {
    for(vector<int>::iterator it = primes.begin(); it != primes.end() && n >= *it; ++it) {
        while(n % *it == 0) {
            n /= *it;
            table[*it].push_back(slug);
        }
    }
    if(n > 1) {
        table[n].push_back(slug);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    fill_n(is_prime, LIM, true);
    primes.push_back(2);
    for(int i = 3; i < LIM; i += 2) {
        if(is_prime[i]) {
            for(int j = i*i; j < LIM; j += i) is_prime[j] = false;
            primes.push_back(i);
        }
    }

    int N, M;
    cin >> N >> M;
    map<int, int> frac;
    for(int i = 0; i < N; ++i) {
        int n;
        cin >> n;
        factoring(n, frac, i);
    }
    vector<int> den(M, 1);
    for(int i = 0; i < M; ++i) {
        int n;
        cin >> n;
        for(vector<int>::iterator it = primes.begin(); it != primes.end() && n >= *it; ++it) {
            while(n % *it == 0) {
                n /= *it;
                if(table[*it].size() > 0) table[*it].pop_back();
                else den[i] *= *it;
            }
        }
        if(n > 1) {
            if(table[n].size() > 0) table[n].pop_back();
            else den[i] *= n;
        }
    }
    vector<int> num(N, 1);
    for(int i = 2; i < 10000000; ++i) {
        if(table[i].size() > 0) {
            for(vector<int>::iterator it = table[i].begin(); it != table[i].end(); ++it) {
                num[*it] *= i;
            }
        }
    }
    cout << num.size() << ' ' << den.size() << endl;
    for(vector<int>::iterator it = num.begin(); it != num.end(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;
    for(vector<int>::iterator it = den.begin(); it != den.end(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;
    return 0;
}
