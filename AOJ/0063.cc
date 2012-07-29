//Name: Palindrome
//Level: 1
//Category: 文字列,やるだけ
//Note:

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int ans = 0;
    string line;
    while(cin >> line) {
        int l = 0, r = line.size()-1;
        bool ok = true;
        while(l < r) {
            if(line[l++] != line[r--]) {
                ok = false;
                break;
            }
        }
        if(ok) ++ans;
    }
    cout << ans << endl;
    return 0;
}
