#include <iostream>
#include <string>

using namespace std;

const string chars[] = {
    "ABC",
    "DEF",
    "GHI",
    "JKL",
    "MNO",
    "PQRS",
    "TUV",
    "WXYZ",
};

int main() {
    string str;
    cin >> str;
    int ans = 0;
    for(string::const_iterator it = str.begin(); it != str.end(); ++it) {
        for(int digit = 2; digit <= 9; ++digit) {
            if(chars[digit-2].find(*it) != string::npos) {
                ans += digit+1;
                break;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
