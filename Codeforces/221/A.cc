//Name: Divisible by Seven
//Level: 3
//Category: 数学,Math
//Note:

/**
 * 1,6,8,9が必ず入ってくることが保障されているが、これらの数を下4桁で適当に並び替えると
 * mod 7で任意の数が作り出せる。
 * したがって、これより前はleading zeroに注意しながら適当に並べ、下4桁で帳尻を合わせれば良い。
 *
 * オーダーはO(N)。
 */
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>

using namespace std;

int ord[1000000];
const string TBL[] = {
    "1869",
    "1968",
    "1689",
    "6198",
    "1698",
    "1986",
    "1896",
};
bool solve() {
    string str;
    if(!(cin >> str)) return false;
    
    const int N = str.size();
    int d = 1;
    for(int i = 0; i < N; ++i) {
        ord[i] = d;
        d *= 10;
        d %= 7;
    }

    int m[10] = {0};
    for(char c : str) {
        m[c-'0']++;
    }
    int rem = 0;
    int o = N-1;
    bool nonzero = false;
    for(int i = 1; i <= 9; ++i) {
        int cnt = m[i];
        if(i == 1 || i == 6 || i == 8 || i == 9) --cnt;
        for(int j = 0; j < cnt; ++j) {
            cout << i;
            rem += ord[o] * i;
            rem %= 7;
            --o;
            nonzero = true;
        }
    }
    if(!nonzero) {
        cout << "1869";
        for(int j = 0; j < m[0]; ++j) {
            cout << 0;
        }
        cout << endl;
    } else {
        for(int j = 0; j < m[0]; ++j) {
            cout << 0;
        }
        cout << TBL[(7-rem) % 7] << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
