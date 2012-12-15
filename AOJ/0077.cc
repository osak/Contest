//Name: Run Length
//Level: 1
//Category: 文字列,やるだけ
//Note:

#include <iostream>
#include <string>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    string str;
    while(cin >> str) {
        for(string::const_iterator it = str.begin(); it != str.end(); ++it) {
            if(*it == '@') {
                ++it;
                int n = *it - '0';
                ++it;
                while(n--) cout << *it;
            } else {
                cout << *it;
            }
        }
        cout << endl;
    }
    return 0;
}
