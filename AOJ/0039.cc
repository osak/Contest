//Name: Roman Figure
//Level: 1
//Category: 文字列,構文解析
//Note:

/*
 * 昇順に文字が並んでいないところは引き算が必要なことに注意する。
 */

#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    string str;
    while(cin >> str) {
        map<char,int> m;
        m['I'] = 1;
        m['V'] = 5;
        m['X'] = 10;
        m['L'] = 50;
        m['C'] = 100;
        m['D'] = 500;
        m['M'] = 1000;

        int ans = 0;
        for(int i = 0; i < str.size(); ++i) {
            char c = str[i];
            if(i+1 < str.size()) {
                char c2 = str[i+1];
                if(m[c] < m[c2]) {
                    ans += m[c2]-m[c];
                    i++;
                    continue;
                }
            }
            ans += m[c];
        }
        cout << ans << endl;
    }
    return 0;
}
