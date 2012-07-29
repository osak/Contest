//Name: Equation
//Level: 2
//Category: 構文解析,全探索
//Note:

/*
 * 変数を2^11通りの割り当てを試し，全てのパターンで左辺と右辺が等しくなるか調べる．
 */
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

typedef string::iterator Iterator;

void skip(Iterator &it, char c) {
    if(*it != c) {
        cerr << "Expected " << c << " but " << *it << endl;
        assert(false);
    }
    ++it;
}

bool formula(Iterator &it, int vars) {
    if(*it == 'T') {
        ++it;
        return true;
    }
    else if(*it == 'F') {
        ++it;
        return false;
    }
    else if('a' <= *it && *it <= 'k') {
        int idx = *it - 'a';
        ++it;
        return (vars & (1<<idx)) != 0;
    }
    else if(*it == '-') {
        ++it;
        bool operand = formula(it, vars);
        return !operand;
    }
    else if(*it == '(') {
        ++it;
        bool lhs = formula(it, vars);
        int op = -1;
        if(*it == '*') {
            ++it;
            op = 1;
        }
        else if(*it == '+') {
            ++it;
            op = 2;
        }
        else if(*it == '-') {
            ++it;
            if(*it == '>') {
                ++it;
                op = 3;
            }
        }
        bool rhs = formula(it, vars);
        skip(it, ')');
        switch(op) {
            case 1:
                return lhs && rhs;
                break;
            case 2:
                return lhs || rhs;
                break;
            case 3:
                return !(lhs && !rhs);
                break;
            default:
                assert(false);
        }
    }
    assert(false);
}

int main() {
    while(true) {
        string str;
        getline(cin, str);
        if(str == "#") break;

        bool ok = true;
        for(int pat = 0; pat < (1<<11); ++pat) {
            Iterator it = str.begin();
            bool lhs = formula(it, pat);
            skip(it, '=');
            bool rhs = formula(it, pat);
            if(lhs != rhs) {
                ok = false;
                break;
            }
        }

        cout << (ok?"YES":"NO") << endl;
    }

    return 0;
}
