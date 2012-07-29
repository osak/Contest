#include <iostream>
#include <string>

using namespace std;

int main() {
    while(!cin.eof()) {
        string str;
        getline(cin, str);
        if(str == "") break;
        for(int shift = 0; shift < 26; ++shift) {
            if(str.find("the") != string::npos || str.find("this") != string::npos || str.find("that") != string::npos) break;
            for(int i = 0; i < str.size(); ++i) 
                if(islower(str[i]) && ++str[i] > 'z') str[i] = 'a';
        }
        cout << str << endl;
    }
    return 0;
}
