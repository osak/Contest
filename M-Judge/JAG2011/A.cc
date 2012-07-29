#include <iostream>
#include <string>

using namespace std;

bool go(const string &str, int &pos, char expect) {
    if(str[pos] == 'm') {
        pos++;
        if(!go(str, pos, 'e')) return false;
    }
    else if(str[pos] == expect) return true;

    if(str[pos] == 'e') {
        pos++;
        if(!go(str, pos, 'w')) return false;
    }
    else return false;

    if(str[pos] == 'w') {
        pos++;
    }
    else return false;

    return pos == str.size() || str[pos] == expect;
}

int main() {
    string s;
    cin >> s;
    int pos = 0;
    cout << (go(s, pos, '\0')?"Cat":"Rabbit") << endl;
    return 0;
}
