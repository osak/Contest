//Name: Smart Calculator
//Level: 2
//Category: 構文解析
//Note:

/**
 * オーソドックスな四則演算の構文解析。
 *
 * オーダーは O(|S|)。
 */
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

typedef string::const_iterator Iterator;

void skip(Iterator &it, char c) {
    if(*it != c) {
        cout << "Expected " << c << " but got " << *it << endl;
        cout << "Parse error near: ";
        while(*it) {
            cout << *it;
            ++it;
        }
        cout << endl;
        abort();
    }
    ++it;
}

long long factor(Iterator&);
long long term(Iterator&);

long long number(Iterator &it) {
    long long val = 0;
    while(isdigit(*it)) {
        val *= 10;
        val += *it - '0';
        ++it;
    }
    return val;
}

long long expr(Iterator &it) {
    long long lhs = term(it);
    while(*it == '+' || *it == '-') {
        const char op = *it;
        skip(it, op);
        const long long rhs = term(it);
        if(op == '+') lhs += rhs;
        else lhs -= rhs;
    }
    return lhs;
}

long long term(Iterator &it) {
    long long lhs = factor(it);
    while(*it == '*' || *it == '/') {
        const char op = *it;
        skip(it, op);
        const long long rhs = factor(it);
        if(op == '*') lhs *= rhs;
        else lhs /= rhs;
    }
    return lhs;
}

long long factor(Iterator &it) {
    if(*it == '(') {
        skip(it, '(');
        const long long val = expr(it);
        skip(it, ')');
        return val;
    } else {
        return number(it);
    }
}

bool solve() {
    string line;
    cin >> line;
    Iterator it = line.begin();
    cout << expr(it) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    while(N--) solve();
    return 0;
}
