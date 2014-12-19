//Name: Doctor's Memorable Codes
//Level: 2
//Category: 文字列,やるだけ
//Note: コピペ可能な変換表はAOJ0088にある

/**
 * 最初の変換はやるだけ。
 * 二段目の変換は、他の符号語のprefixになっているような符号語が存在しないため、どれかの符号語にマッチするまで貪欲に取っていけば良い。
 *
 * オーダーは O(|S|)。
 */
#include <iostream>
#include <string>
#include <map>

using namespace std;

string conv(char c) {
    int ord = c - 'A';
    string res;
    for(int i = 4; i >= 0; --i) {
        if(ord & (1<<i)) res += "1";
        else res += "0";
    }
    return res;
}

bool solve() {
    string line;
    if(!getline(cin, line)) return false;

    string code;
    for(char c : line) {
        switch(c) {
        case ' ':
            code += "11010";
            break;
        case '.':
            code += "11011";
            break;
        case ',':
            code += "11100";
            break;
        case '-':
            code += "11101";
            break;
        case '\'':
            code += "11110";
            break;
        case '?':
            code += "11111";
            break;
        default:
            code += conv(c);
        }
    }

    map<string,char> dict;
    dict["101"] = ' ';
    dict["000000"] = '\'';
    dict["000011"] = ',';
    dict["10010001"] = '-';
    dict["010001"] = '.';
    dict["000001"] = '?';
    dict["100101"] = 'A';
    dict["10011010"] = 'B';
    dict["0101"] = 'C';
    dict["0001"] = 'D';
    dict["110"] = 'E';
    dict["01001"] = 'F';
    dict["10011011"] = 'G';
    dict["010000"] = 'H';
    dict["0111"] = 'I';
    dict["10011000"] = 'J';
    dict["0110"] = 'K';
    dict["00100"] = 'L';
    dict["10011001"] = 'M';
    dict["10011110"] = 'N';
    dict["00101"] = 'O';
    dict["111"] = 'P';
    dict["10011111"] = 'Q';
    dict["1000"] = 'R';
    dict["00110"] = 'S';
    dict["00111"] = 'T';
    dict["10011100"] = 'U';
    dict["10011101"] = 'V';
    dict["000010"] = 'W';
    dict["10010010"] = 'X';
    dict["10010011"] = 'Y';
    dict["10010000"] = 'Z';

    string ans, buf;
    for(char c : code) {
        buf += c;
        auto it = dict.find(buf);
        if(it != end(dict)) {
            ans += it->second;
            buf = "";
        }
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
