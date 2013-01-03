#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <cassert>

using namespace std;

struct Function {
    char name;
    unsigned and_val, or_val, xor_val;

    Function() {}
    Function(char n) : name(n), and_val(0x7fffffff), or_val(0), xor_val(0) {}
    //Function(int a, int o, int x) : and_val(a), or_val(o), xor_val(x) {}
    unsigned call(unsigned n, unsigned times) const {
        unsigned res = n;
        if(times == 0) return res;
        res &= and_val;
        res |= or_val;
        if(times % 2 == 1) res ^= xor_val;
        return res;
    }
};

void print_func(const Function &func) {
    cout << func.name << "(x)=";
    cout << "(((x|" << func.or_val << ")";
    cout << "^" << func.xor_val << ")";
    cout << "&" << func.and_val << ")";
    cout << endl;
}

typedef string::iterator Iterator;

void skip_(Iterator &it, char c, int line) {
    if(*it != c) {
        cerr << "Parse error from line " << line << endl;
        abort();
    }
    ++it;
}
#define skip(it,c) skip_(it, c, __LINE__)

unsigned number(Iterator &it) {
    unsigned res = 0;
    while(isdigit(*it)) {
        res *= 10;
        res += *it - '0';
        ++it;
    }
    return res;
}

pair<char,unsigned> function(Iterator &it) {
    char name = *it++;
    unsigned times = 1;
    if(*it == '^') {
        skip(it, '^');
        times = number(it);
    }
    //cout << "Function call: " << name << ' ' << times << endl;
    return make_pair(name, times);
}

unsigned expr(Iterator &it, unsigned val, map<char,Function> &funcs) {
    if(*it == 'x') {
        ++it;
        return val;
    } else if(isdigit(*it)) {
        return number(it);
    } else if('a' <= *it && *it <= 'j') {
        pair<char,unsigned> func = function(it);
        skip(it, '(');
        unsigned arg = expr(it, val, funcs);
        //cout << func.first << ' ' << arg << endl;
        skip(it, ')');
        //print_func(funcs[func.first]);
        unsigned res = funcs[func.first].call(arg, func.second);
        //cout << "res " << res << endl;
        return res;
    } else if(*it == '(') {
        skip(it, '(');
        unsigned lhs = expr(it, val, funcs);
        char op = *it++;
        unsigned rhs = expr(it, val, funcs);
        skip(it, ')');
        switch(op) {
            case  '|':
                return lhs | rhs;
            case '^':
                return lhs ^ rhs;
            case '&':
                //cout << "opr " << lhs << "&" << rhs << ' ' << (lhs & rhs) << endl;
                return lhs & rhs;
        }
    }
    cerr << *it << endl;
    assert(!"MUST NOT COME!");
}

Function parse(Iterator &it, map<char,Function> &funcs) {
    char name = *it++;
    skip(it, '(');
    skip(it, 'x');
    skip(it, ')');
    skip(it, '=');
    Function f(name);
    for(int bit = 0; bit < 31; ++bit) {
        unsigned mask = (1<<bit);
        Iterator it_copy = it;
        unsigned zero = expr(it_copy, 0, funcs) & mask;
        it_copy = it;
        unsigned one = expr(it_copy, mask, funcs) & mask;
        //cout << zero << ' ' << one << endl;
        if(zero == 0 && one == 0) {
            f.and_val &= ~mask;
        } else if(zero != 0 && one == 0) {
            f.xor_val |= mask;
        } else if(zero != 0 && one != 0) {
            f.or_val |= mask;
        }
    }
    return funcs[name] = f;
}


int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int N;
    cin >> N;
    cin.ignore();
    map<char,Function> funcs;
    for(int i = 0; i < N; ++i) {
        string line;
        getline(cin, line);
        Iterator it = line.begin();
        Function func = parse(it, funcs);
        print_func(func);
    }
    return 0;
}

