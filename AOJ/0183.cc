//Name: Black-and-White
//Level: 1
//Category: 実装
//Note:

/**
 * 縦、横、斜めそれぞれについて、同じ文字が1列に並んでいるか、並んでいればどの文字かを判定する。
 */
#include <iostream>
#include <string>
#include <array>

using namespace std;

array<string,3> field;
char check_inner(int r, int c, int dr, int dc) {
    if(field[r][c] == field[r+dr][c+dc] && field[r][c] == field[r+dr*2][c+dc*2]) {
        return field[r][c];
    }
    return 0;
}

string check() {
    // Row
    for(int r = 0; r < 3; ++r) {
        char c = check_inner(r, 0, 0, 1);
        if(c != 0 && c != '+') return string()+c;
    }

    // Col
    for(int c = 0; c < 3; ++c) {
        char cc = check_inner(0, c, 1, 0);
        if(cc != 0 && cc != '+') return string()+cc;
    }

    // Diag
    {
        char c = check_inner(0, 0, 1, 1);
        if(c != 0 && c != '+') return string()+c;
    }
    {
        char c = check_inner(0, 2, 1, -1);
        if(c != 0 && c != '+') return string()+c;
    }
    return "NA";
}

bool solve() {
    for(int i = 0; i < 3; ++i) {
        cin >> field[i];
        if(field[i] == "0") return false;
    }

    cout << check() << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
