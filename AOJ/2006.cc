//Name: Keitai Message
//Level: 1
//Category: シミュレーション,やるだけ
//Note: 

/**
 * やるだけ。
 */
#include <iostream>
#include <string>

using namespace std;

const string tbl[10] = {
    "",
    ".,!? ",
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz"
};
bool solve(bool first) {
    string cmd;
    string ans;
    cin >> cmd;
    int row = 0, col = -1;
    for(char c : cmd) {
        if(c == '0') {
            if(col >= 0) ans += tbl[row][col % tbl[row].size()];
            col = -1;
        } else {
            row = c - '0';
            ++col;
        }
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    int N;
    cin >> N;
    bool first = true;
    while(N--) {
        solve(first);
        first = false;
    }
    return 0;
}
