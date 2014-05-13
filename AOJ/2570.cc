//Name: Sipura
//Level: 3
//Category: 文字列,String,構文解析
//Note:

/**
 * 逆から読んでいくとLL(1)になる。
 * オーダーはO(N)。
 */
#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

using namespace std;

typedef unsigned long long LL;
const LL MOD = 1000000007LL;

void skip(const string &s, int &pos) {
    while(pos >= 0 && s[pos] == ' ') --pos;
}

LL number(const string &s, int &pos) {
    skip(s, pos);
    LL val = 0;
    LL ord = 1;
    while(pos >= 0 && isdigit(s[pos])) {
        val += ord * (s[pos] - '0');
        ord *= 10;
        --pos;
    }
    return val;
}

LL expr(const string &s, int &pos) {
    skip(s, pos);
    LL val = 0;
    if(isdigit(s[pos])) {
        val = number(s, pos);
    } else if(s[pos] == '>') {
        --pos;
        val = expr(s, pos);
        val = (val*val) % MOD;
    } else {
        cerr << s << ' ' << pos << endl;
        assert(false);
    }
    skip(s, pos);
    if(pos >= 0) {
        if(s[pos] == '>' && s[pos-1] == '>') {
            pos -= 2;
            const LL lhs = expr(s, pos);
            if(val > 63) val = 0;
            else val = lhs >> val;
        } else if(s[pos] == '<') {
            --pos;
        } else {
            assert(false);
        }
    }
    //cout << val << "(" << pos << ")" << endl;
    return val;
}

bool solve() {
    string str;
    getline(cin, str);
    if(str == "#") return false;

    int pos = str.size()-1;
    for(char &c : str) {
        if(c == 'S') c = ' ';
    }
    cout << expr(str, pos) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
