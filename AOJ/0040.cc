//Name: Affine Cipher
//Level: 1
//Category: 文字列,数論
//Note:

/*
 * aとbの範囲が簡単に分かるので、全パターンで変換テーブルを作成し、実際に復号を試す。
 */
#include <iostream>
#include <string>

using namespace std;

string table(int a, int b) {
    string str;
    for(int i = 'a'; i <= 'z'; ++i)
        str += ((i-'a')*a+b) % 26 + 'a';
    string rev;
    rev.resize(26);
    for(int i = 0; i < str.size(); ++i)
        rev[str[i]-'a'] = i+'a';
    return rev;
}

int main() {
    int N;
    cin >> N;
    cin.ignore();
    while(N--) {
        string str;
        getline(cin, str);
        for(int a = 0; a < 26; ++a) {
            if(a % 2 == 0 || a % 13 == 0) continue;
            for(int b = 0; b < 26; ++b) {
                string tbl = table(a, b);
                string tmp = str;
                for(int i = 0; i < tmp.size(); ++i) 
                    if(tmp[i] != ' ') tmp[i] = tbl[tmp[i]-'a'];
                if(tmp.find("that") != string::npos || tmp.find("this") != string::npos) {
                    cout << tmp << endl;
                    goto next;
                }
            }
        }
next:
        ;
    }
    return 0;
}
