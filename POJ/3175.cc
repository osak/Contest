//Name: Finding Bovine Roots
//Level: 4
//Category: 数論,全探索
//Note: 計算量あやしい

/*
 * 小数点以下をDとすると，求める数値 x は
 * (n + D)^2 ≦ x < (n + D + 1e-L)^2
 * を満たす．
 * これに対して n を線形探索すれば間にあう．
 *
 * 計算量は見積れていない．
 */
#define _GLIBCXX_DEBUG
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <limits>
#include <cstdio>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)

typedef unsigned long long ULL;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int L;
    cin >> L;
    ULL decimal;
    cin >> decimal;
    ULL ord = 1;
    for(int i = 0; i < L; ++i) ord *= 10;

    long double dec = static_cast<long double>(decimal) / ord;
    long double dec_sup = static_cast<long double>(decimal+1) / ord;
    for(int n = 0; ; ++n) {
        ULL inf = ceill((n+dec)*(n+dec));
        ULL sup = floorl((n+dec_sup)*(n+dec_sup) - 1e-14);
        if(inf <= sup) {
            cout << inf << endl;
            break;
        }
    }
    return 0;
}
