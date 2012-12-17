//Name: The Code A Doctor Loved
//Level: 1
//Category: 文字列,やるだけ
//Note:

#include <iostream>
#include <string>
#include <map>

using namespace std;

const string STBL1 = " ',-.?ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string CODE1[] = {
"101", "000000", "000011", "10010001", "010001", "000001", "100101", "10011010", "0101", "0001", "110", "01001", "10011011", "010000", "0111", "10011000", "0110", "00100", "10011001", "10011110", "00101", "111", "10011111", "1000", "00110", "00111", "10011100", "10011101", "000010", "10010010", "10010011", "10010000",
};
const string STBL2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ .,-'?";

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    map<char,string> dict;
    for(int i = 0; i < 32; ++i) {
        dict[STBL1[i]] = CODE1[i];
    }

    string line;
    while(getline(cin, line)) {
        string codestr;
        for(string::const_iterator it = line.begin(); it != line.end(); ++it) {
            codestr += dict[*it];
        }
        codestr += string((5-codestr.size()%5) % 5, '0');
        string res;
        for(int i = 0; i < codestr.size(); i += 5) {
            const string num = codestr.substr(i, 5);
            int val = 0;
            for(int j = 0; j < 5; ++j) {
                val <<= 1;
                val += num[j]-'0';
            }
            res += STBL2[val];
        }
        cout << res << endl;
    }
    return 0;
}
