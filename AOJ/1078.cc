//Name: SAT-EN-3
//Level: 3
//Category: 構文解析
//Note:

/**
 * 加法標準形なので、X&~Xの形を含まない項があればその項は真にでき、全体も真になる。
 *
 * オーダーは O(|S|)。
 */
#include <iostream>
#include <string>
#include <cassert>
#include <map>

using namespace std;

pair<char,bool> literal(const string &str, int &pos) {
    pair<char,bool> res('\0', false);
    if(str[pos] == '~') {
        res.second = true;
        ++pos;
    }
    res.first = str[pos++];
    return res;
}

bool parse(const string &str, int pos) {
    if(pos >= str.size()) return false;
    if(str[pos] == '|') ++pos;
    assert(str[pos] == '(');
    ++pos;
    map<char,bool> vars;
    bool ok = true;
    for(int i = 0; i < 3; ++i) {
        pair<char,bool> var = literal(str, pos);
        if(vars.count(var.first) && vars[var.first] != var.second) {
            ok = false;
        }
        vars[var.first] = var.second;
        if(i != 2) {
            assert(str[pos] == '&');
            ++pos;
        }
    }
    assert(str[pos] == ')');
    ++pos;
    if(ok) return true;
    else return parse(str, pos);
}

bool solve() {
    string str;
    if(!(cin >> str)) return false;
    if(str == "#") return false;

    cout << (parse(str, 0) ? "yes" : "no") << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) ;
    return 0;
}
