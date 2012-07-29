#include <cstring>
#include <iostream>
#include <cassert>
using namespace std;

//typedef string::const_iterator State;
typedef const char * State;

bool formula(State &st, int i);
bool parse(State &st, int i) {
    bool ret = formula(st, i);
    //assert(*st == '=' || *st == '\0');
    return ret;
}

bool formula(State &st, int i) {
    if (*st == 'T') {
        st++;
        return true;
    } else if (*st == 'F') {
        st++;
        return false;
    } else if ('a' <= *st && *st <= 'k') {
        int t = (*st - 'a');
        st++;
        if ((i & (1 << t)) != 0) {
            return true;
        } else {
            return false;
        }
    } else if (*st == '-') {
        st++;
        bool inv = formula(st, i);
        return !inv;
    } else if (*st == '(') {
        st++;
        bool lhs = formula(st, i);
        int op = -1;
        if (*st == '*') {
            st++;
            op = 1;
        } else if (*st == '+') {
            st++;
            op = 2;
        } else if (*st == '-') {
            st++;
            if (*st == '>') {
                st++;
                op = 3;
            }
        }
        if (op == -1) assert(false);

        bool rhs = formula(st, i);
        assert(*st == ')');
        st++;

        if (op == 1) {
            return lhs && rhs;
        } else if (op == 2) {
            return lhs || rhs;
        } else if (op == 3) {
            return !(lhs && !rhs);
        }
    }

    assert(false);
}

int main(void) {
    while (true) {
        //string str;
        //cin >> str;
        //getline(cin, str);
        char str[2048];
        scanf(" %s ", str);
        if (str[0] == '#') break;

        bool ret = true;
        for (int i = 0; i < (1 << 11); i++) {
            State state = str;
            bool lhs = parse(state, i);
            state++;
            bool rhs = parse(state, i);

            if (lhs != rhs) {
                ret = false;
                break;
            }
        }
        if (ret) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
