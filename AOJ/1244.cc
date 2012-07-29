#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>
#include <cassert>

using namespace std;

void skip(const string &str, int &pos, char c) {
    if(str[pos] != c) cerr << "Expected " << c << " but " << str[pos] << endl;
    ++pos;
}

string atom(const string &str, int &pos) {
    assert(isupper(str[pos]));

    string name = "";
    name += str[pos];
    ++pos;
    if(pos < str.size() && islower(str[pos])) {
        name += str[pos++];
    }
    return name;
}

int number(const string &str, int &pos) {
    assert(isdigit(str[pos]));

    int cur = 0;
    while(pos < str.size() && isdigit(str[pos])) {
        cur *= 10;
        cur += str[pos++]-'0';
    }
    return cur;
}

int molecule(const string &str, int &pos, map<string,int> &tbl) {
    int sum = 0;
    for(; pos < str.size(); ) {
        //cout << pos << ' ' << str[pos] << endl;
        if(str[pos] == '(') {
            skip(str, pos, '(');
            int w = molecule(str, pos, tbl);
            skip(str, pos, ')');
            int n = number(str, pos);
            sum += w*n;
        }
        else if(str[pos] == ')') {
            break;
        }
        else {
            string a = atom(str, pos);
            //cout << "atom " << a << endl;
            if(tbl.count(a) == 0) throw "UNKNOWN";

            int n = 1;
            if(pos < str.size() && isdigit(str[pos])) {
                n = number(str, pos);
            }
            //cout << "number " << n << ' ' << pos << endl;
            sum += tbl[a] * n;
        }
    }

    return sum;
}

int main() {
    map<string, int> tbl;
    while(true) {
        string atom;
        cin >> atom;
        if(atom == "END_OF_FIRST_PART") break;

        int weight;
        cin >> weight;
        tbl[atom] = weight;
    }

    while(true) {
        string exp;
        cin >> exp;
        if(exp == "0") break;

        try {
            int pos = 0;
            cout << molecule(exp, pos, tbl) << endl;
        } catch(const char *str) {
            cout << "UNKNOWN" << endl;
        }
    }

    return 0;
}
