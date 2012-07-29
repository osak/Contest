/*
 * オートマトンを実装する．
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(0);

    string str;
    getline(cin, str);

    int ans = 0;
    char state = 'J';
    int accj = 0, acco = 0, acci = 0;
    for(string::iterator it = str.begin(); it != str.end(); ++it) {
        //cout << state << endl;
        switch(state) {
            case 'J':
                switch(*it) {
                    case 'J':
                        ++accj;
                        break;
                    case 'O':
                        acco = 1;
                        state = 'O';
                        if(acco > accj) {
                            accj = 0;
                            state = 'J';
                        }
                        break;
                    case 'I':
                        accj = 0;
                        break;
                }
                break;
            case 'O':
                switch(*it) {
                    case 'J':
                        accj = 1;
                        state = 'J';
                        break;
                    case 'O':
                        if(++acco > accj) {
                            accj = 0;
                            state = 'J';
                        }
                        break;
                    case 'I':
                        acci = 1;
                        state = 'I';
                        if(acci == acco) {
                            ans = max(ans, acci);
                        }
                        break;
                }
                break;
            case 'I':
                switch(*it) {
                    case 'J':
                        accj = 1;
                        state = 'J';
                        break;
                    case 'O':
                        accj = 0;
                        state = 'J';
                    case 'I':
                        if(++acci == acco) {
                            ans = max(ans, acci);
                        }
                        break;
                }
                break;
        }
    }

    cout << ans << endl;

    return 0;
}
