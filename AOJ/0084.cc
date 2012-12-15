//Name: Search Engine
//Level: 1
//Category: 文字列,やるだけ
//Note:

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    string str;
    getline(cin, str);
    for(string::iterator it = str.begin(); it != str.end(); ++it) {
        if(*it == ' ' || *it == '.' || *it == ',') *it = ' ';
    }
    istringstream is(str);
    string chunk;
    bool first = true;
    while(is >> chunk) {
        if(chunk.size() >= 3 && chunk.size() <= 6) {
            if(!first) cout << ' ';
            cout << chunk;
            first = false;
        }
    }
    cout << endl;
    return 0;
}
