//Name: Secret Number
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    int ans = 0;
    string line;
    while(cin >> line) {
        int v = 0;
        for(int i = 0; i < line.size(); ++i) {
            if(isdigit(line[i])) {
                v *= 10;
                v += line[i]-'0';
            }
            else {
                ans += v;
                v = 0;
            }
        }
        ans += v;
    }
    cout << ans << endl;
    return 0;
}
