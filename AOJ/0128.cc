//Name: Abacus
//Level: 2
//Category: 文字列
//Note: 

/**
 * やり方は色々あるが、最初に全体が収まるバッファを取っておき、1桁ずつ埋めていくとよい。
 *
 * オーダーは O(log N)。
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool solve(bool first) {
    int N;
    if(!(cin >> N)) return false;

    if(!first) cout << endl;
    vector<string> f(8, string(5, ' '));
    for(int i = 4; i >= 0; --i) {
        int d = N % 10;
        N /= 10;

        f[2][i] = '=';
        if(d >= 5) {
            f[1][i] = '*';
            d -= 5;
        } else {
            f[0][i] = '*';
        }
        for(int j = 0; j < 5; ++j) {
            if(d == j) continue;
            f[j+3][i] = '*';
        }
    }
    for(const string &s : f) {
        cout << s << endl;
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
