#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

using namespace std;

string parse(const string &str, int &pos);

void skip(const string &str, int &pos, char c) {
    assert(str[pos] == c);
    ++pos;
}

string sexpr(const string &str, int &pos) {
    string res = "(";
    string elem = "";
    bool last = false;
    for(; pos < str.size(); ) {
        if(res != "(") res += " ";
        res += parse(str, pos);
        if(last) break;

        if(pos < str.size() && str[pos] == ',') {
            ++pos;
            skip(str, pos, ' ');
            continue;
        }
        else if(str.compare(pos, 5, " and ") == 0) {
            pos += 5;
            last = true;
            continue;
        }
    }

    return res + ")";
}

string parse(const string &str, int &pos) {
    static const string LISTSTR = "a list of ";
    string res = "";
    if(str.compare(pos, LISTSTR.size(), LISTSTR) == 0) {
        pos += LISTSTR.size();
        res += sexpr(str, pos);
    }
    else {
        for(; pos < str.size(); ++pos) {
            if(isupper(str[pos])) res += str[pos];
            else break;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    int N;
    cin >> N;
    cin.ignore();
    while(N--) {
        string str;
        getline(cin, str);
        //str.erase(str.begin()+str.size()-1);

        int lists = 0;
        int pos = 0;
        while((pos = str.find("list", pos)) != string::npos) {
            ++lists;
            ++pos;
        }
        int ands = 0;
        pos = 0;
        while((pos = str.find("and", pos)) != string::npos) {
            ++ands;
            ++pos;
        }

        if(ands > 0 && ands != lists) {
            pos = str.rfind("of ") + 3;
            for(; pos < str.size(); ++pos) {
                if(!isupper(str[pos])) goto amb;
            }
            ++ands;
        }

        if(ands > 0 && ands != lists) {
amb:
            cout << "AMBIGUOUS" << endl;
            continue;
        }

        pos = 0;
        cout << parse(str, pos) << endl;
    }
    return 0;
}
