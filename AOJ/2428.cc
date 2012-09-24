//Name: Lost Number
//Level: 2
//Category: 構文解析
//Note:

/*
 * 構文解析やるだけ．
 * ()の中には最低1つ演算子が入っていないという制約に注意．
 */
#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

typedef string::iterator Iterator;
const int LIMIT = 1<<10;

int number(Iterator &it) {
    int val = 0;
    if(!isdigit(*it)) throw "not a number";
    while(isdigit(*it)) {
        val <<= 1;
        val += *it - '0';
        if(val >= LIMIT) throw "limit over";
        ++it;
    }
    return val;
}

int expression(Iterator &it, bool &operated);
int factor(Iterator &it, bool &operated) {
    if(*it == '(') {
        ++it;
        bool opr = false;
        int val = expression(it, opr);
        if(*it == ')' && opr) {
            ++it;
            return val;
        } else {
            throw "Illegal paren";
        }
    } else {
        return number(it);
    }
    throw "error";
}
int term(Iterator &it, bool &operated) {
    int lhs = factor(it, operated);
    while(*it == '*') {
        ++it;
        lhs *= factor(it, operated);
        if(lhs < 0 || lhs >= LIMIT) throw "limit over";
        operated = true;
    }
    return lhs;
}

int expression(Iterator &it, bool &operated) {
    int lhs = term(it, operated);
    while(*it == '+' || *it == '-') {
        char op = *it;
        ++it;
        if(op == '+') {
            lhs += term(it, operated);
        } else if(op == '-') {
            lhs -= term(it, operated);
        }
        operated = true;
        if(lhs < 0 || lhs >= LIMIT) throw "limit over";
    }
    return lhs;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    string str;
    cin >> str;
    vector<int> dotpos;
    for(int i = 0; i < str.size(); ++i) {
        if(str[i] == '.') dotpos.push_back(i);
    }
    int allpat = 1;
    for(int i = 0; i < dotpos.size(); ++i) {
        allpat *= 7;
    }
    int ans = -1;
    for(int pat = 0; pat < allpat; ++pat) {
        int tmp = pat;
        string expr(str);
        for(int i = 0; i < dotpos.size(); ++i) {
            int n = tmp % 7;
            tmp /= 7;
            expr[dotpos[i]] = "01+-*()"[n];
        }
        try {
            bool dmy;
            Iterator it = expr.begin();
            int val = expression(it, dmy);
            if(val < 0 || val >= LIMIT) throw "limit over";
            if(it != expr.end()) throw "premature end";
            ans = max(ans, val);
        } catch (const char *msg) {
            //cout << expr << ' ' << msg << endl;
        }
    }
    cout << ans << endl;
    return 0;
}
