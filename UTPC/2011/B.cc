#include <iostream>
#include <string>

using namespace std;

int main() {
    string str;
    cin >> str;

    int cnt = 0;
    for(int i = 0; i < str.size()/2; ++i) {
        int op = str.size()-i-1;
        if((str[i] == 'i' && str[op] != 'i') ||
           (str[i] == 'w' && str[op] != 'w') ||
           (str[i] == '(' && str[op] != ')') ||
           (str[i] == ')' && str[op] != '('))
        {
            ++cnt;
        }
    }
    if(str.size() % 2 != 0) {
        char mid = str[str.size()/2];
        if(mid != 'i' && mid != 'w') ++cnt;
    }
    cout << cnt << endl;
    return 0;
}
