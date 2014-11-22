//Name: Dimensional Analysis
//Level: 3
//Category: 構文解析
//Note:

/**
 * 次元のみを考えて構文解析する。
 * チェックすべき点は、加減算で次元が一致していることと、乗除算で次元の変換が発生すること。
 *
 * オーダーは O(|S|N)。
 */
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <map>

using namespace std;

typedef vector<int> Unit;
typedef string::const_iterator Iterator;

struct DimensionMismatch{};

struct Parser {
    map<string,Unit> &vars;
    Parser(map<string,Unit> &vars) : vars(vars) {}

    Unit variable(Iterator &it) {
        string buf;
        while(isalpha(*it)) buf += *it++;
        return vars[buf];
    }

    Unit factor(Iterator &it) {
        if(*it == '(') {
            ++it;
            Unit val = formula(it);
            ++it;
            return val;
        } else {
            return variable(it);
        }
    }

    Unit term(Iterator &it) {
        Unit lhs = factor(it);
        while(*it == '*' || *it == '/') {
            const char op = *it++;
            Unit rhs = factor(it);
            const int f = (op == '*' ? 1 : -1);
            for(int i = 0; i < lhs.size(); ++i) {
                lhs[i] += rhs[i] * f;
            }
        }
        return lhs;
    }

    Unit formula(Iterator &it) {
        Unit lhs = term(it);
        while(*it == '+' || *it == '-') {
            ++it;
            Unit rhs = term(it);
            if(lhs != rhs) throw DimensionMismatch();
        }
        return lhs;
    }

    Unit parse(const string &str) {
        Iterator it = str.begin();
        return formula(it);
    }
};

bool solve() {
    int N, M, P;
    if(!(cin >> N >> M >> P)) return false;
    if(!N && !M && !P) return false;

    map<string,Unit> dict, vars;
    map<Unit,string> rev_dict;
    for(int i = 0; i < M; ++i) {
        string name;
        cin >> name;
        Unit u(N);
        for(int j = 0; j < N; ++j) {
            cin >> u[j];
        }
        dict[name] = u;
        rev_dict[u] = name;
    }
    string formula;
    cin >> formula;
    for(int i = 0; i < P; ++i) {
        string name, uname;
        cin >> name >> uname;
        vars[name] = dict[uname];
    }
    try {
        Parser parser(vars);
        Unit res = parser.parse(formula);
        if(rev_dict.count(res)) {
            cout << rev_dict[res] << endl;
        } else {
            cout << "undefined" << endl;
        }
    } catch(DimensionMismatch &d) {
        cout << "error" << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
