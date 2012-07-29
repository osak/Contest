#include <iostream>
#include <string>

using namespace std;

const string table[] = {
    "",
    "',.!?",
    "abcABC",
    "defDEF",
    "ghiGHI",
    "jklJKL",
    "mnoMNO",
    "pqrsPQRS",
    "tuvTUV",
    "wxyzWXYZ",
};

int main() {
    string s;
    while(cin >> s && !cin.eof()) {
        char cur = s[0];
        int seq = 1;
        for(int i = 1; i < s.size(); ++i) {
            if(s[i] == cur) ++seq;
            else {
                int idx = cur-'0';
                if(idx == 0) for(int j = 0; j < seq-1; ++j) cout << ' ';
                else cout << table[idx][(seq-1) % table[idx].size()];

                cur = s[i];
                seq = 1;
            }
        }
        int idx = cur-'0';
        if(idx == 0) for(int j = 0; j < seq-1; ++j) cout << ' ';
        else cout << table[idx][(seq-1) % table[idx].size()];
        cout << endl;
    }
    return 0;
}

