//Name: CatChecker
//Level: 2
//Category: 構文解析
//Note:

/*
 * やるだけ
 */
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef string::iterator Iterator;

void cat(Iterator &it) {
    if(*it != 'm') return;
    ++it;
    if(*it == 'm') cat(it);
    if(*it != 'e') throw "Not Cat";
    ++it;
    if(*it == 'm') cat(it);
    if(*it != 'w') throw "Not Cat";
    ++it;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    string str;
    while(cin >> str) {
        Iterator it = str.begin();
        bool iscat = true;
        if(it != str.end()) {
            try {
                cat(it);
                if(it != str.end()) iscat = false;
            } catch(const char *msg) {
                iscat = false;
            }
        }
        cout << (iscat?"Cat":"Rabbit") << endl;
    }
    return 0;
}
