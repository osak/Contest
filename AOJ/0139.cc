//Name: Snakes
//Level: 2
//Category: 文字列,オートマトン
//Note: 

/**
 * AとBは別々に判定する。
 */
#include <iostream>
#include <string>

using namespace std;

bool snakeA(const string &s) {
    auto it = begin(s);
    int cnt = 0;
    if(*it++ != '>') return false;
    if(*it++ != '\'') return false;
    while(true) {
        const char c = *it++;
        if(c == '#') break;
        else if(c == '=') ++cnt;
        else return false;
    }
    if(cnt == 0) return false;
    while(cnt--) {
        if(*it++ != '=') return false;
    }
    if(*it++ != '~') return false;
    return it == end(s);
}

bool snakeB(const string &s) {
    auto it = begin(s);
    if(*it++ != '>') return false;
    if(*it++ != '^') return false;
    bool ok = false;
    while(true) {
        const char c = *it++;
        if(c == '~') break;
        else if(c != 'Q') return false;

        if(*it++ != '=') return false;
        ok = true;
    }
    if(!ok) return false;
    if(*it++ != '~') return false;
    return it == end(s);
}

bool solve(bool first) {
    string s;
    cin >> s;
    if(snakeA(s)) cout << "A" << endl;
    else if(snakeB(s)) cout << "B" << endl;
    else cout << "NA" << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(2);

    bool first = true;
    int N;
    cin >> N;
    while(N-- && solve(first)) {
        first = false;
    }
    return 0;
}
