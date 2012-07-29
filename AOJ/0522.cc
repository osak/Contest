#include <iostream>
#include <string>

using namespace std;

int main() {
    while(true) {
        string s;
        if(!(cin >> s)) break;

        int joi = 0;
        int ioi = 0;

        for(int i = 0; i < s.size()-2; ++i) {
            if(s[i] == 'J') {
                if(s[i+1] == 'O' && s[i+2] == 'I') ++joi;
            }
            if(s[i] == 'I') {
                if(s[i+1] == 'O' && s[i+2] == 'I') ++ioi;
            }
        }
        cout << joi << endl;
        cout << ioi << endl;
    }
    return 0;
}
