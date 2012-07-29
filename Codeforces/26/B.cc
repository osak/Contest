#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int open = 0;
    string str;
    cin >> str;

    int len = str.size();
    for(int i = 0; i < str.size(); ++i) {
        if(str[i] == '(') {
            ++open;
        }
        else if(str[i] == ')') {
            if(open == 0) --len;
            else --open;
        }
    }
    len -= open;
    cout << len << endl;

    return 0;
}
