//Name: Caesar Cipher
//Level: 2
//Category: 文字列,暗号
//Note:

#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;
    for(int i = 0; i < s.size(); ++i) {
        cout << char((s[i]-'A'-3+26)%26+'A');
    }
    cout << endl;
    return 0;
}
