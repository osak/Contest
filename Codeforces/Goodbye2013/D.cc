//Name: New Year Letter
//Level: 3
//Category: 数学,Math
//Note:

/**
 * 最初の文字列をs1=1..2, s2=3..4とすると、これらがくっつくことによって
 * 23, 43, 41のパターンで新しくACが生成される。
 * これらの出現数は漸化式で求められる。
 * また、s1, s2そのものに含まれているACも出現数だけ複製される。
 * これらを、23, 43, 41の各パターンを使う時と使わないときで全探索する。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long LL;

LL fib[60];
LL fib2[60];

string generate(int acs, int len) {
    string str;
    while(acs--) str += "AC";
    while((int)str.size() < len) str += "X";
    return str;
}

bool solve() {
    fib[0] = fib[1] = 1;
    for(int i = 2; i < 60; ++i) {
        fib[i] = fib[i-2] + fib[i-1];
    }
    fib2[0] = fib2[1] = 1;
    for(int i = 2; i < 60; ++i) {
        fib2[i] = fib2[i-2] + fib2[i-1] + ((i+1)%2);
    }


    LL K, X, N, M;
    if(!(cin >> K >> X >> N >> M)) return false;
    --K;
    LL x12 = fib[K-2];
    if(K == 0) x12 = 1;
    if(K == 1) x12 = 0;
    const LL x34 = K >= 1 ? fib[K-1] : 0;
    const LL x23 = K >= 2 ? fib[K-2] : 0;
    const LL x41 = K >= 3 ? fib2[K-3] : 0;
    const LL x43 = K >= 4 ? fib2[K-4] : 0;

    //cout << x23 << ' ' << x41 << ' ' << x43 << endl;
    for(int pat = 0; pat <= 7; ++pat) {
        int mask1 = 0, mask2 = 0;
        LL add = 0;
        if(pat & 1) {
            mask1 |= (1<<2);
            mask2 |= (1<<3);
            add += x23;
        }
        if(pat & 2) {
            mask2 |= (1<<3);
            mask2 |= (1<<4);
            add += x43;
        }
        if(pat & 4) {
            mask1 |= (1<<1);
            mask2 |= (1<<4);
            add += x41;
        }
        const LL lenN = N - __builtin_popcount(mask1);
        const LL lenM = M - __builtin_popcount(mask2);
        //cout << pat << ' ' << add << endl;
        if(add > X) continue;
        for(int cnt1 = 0; cnt1 <= lenN/2; ++cnt1) {
            LL rem = X - cnt1*x12 - add;
            //cout << pat << ' ' << cnt1 << ' ' << rem << endl;
            if(rem >= 0 && rem % x34 == 0 && rem/x34*2 <= lenM) {
                string s1 = "";
                if(mask1 & (1<<1)) s1 += "C";
                s1 += generate(cnt1, lenN);
                if(mask1 & (1<<2)) s1 += "A";

                string s2 = "";
                if(mask2 & (1<<3)) s2 += "C";
                s2 += generate(rem / x34, lenM);
                if(mask2 & (1<<4)) s2 += "A";

                cout << s1 << endl;
                cout << s2 << endl;
                return true;
            }
        }
    }
    cout << "Happy new year!" << endl;
    return true;
}
    
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
