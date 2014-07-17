//Name: D's Ambition
//Level: 1
//Category: 文字列
//Note: RUPC 2014 Day3

/**
 * ある文字がAIDUNYANのアナグラムに含まれているとき、対応する部分文字列は一意に定まるという条件があるので、
 * 各文字の出現数を数えながら処理する。
 *
 * オーダーはO(|D|)。
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool solve() {
    string str;
    if(!(cin >> str)) return false;

    vector<int> cnt(26, 0), target(26, 0);
    for(char c : string("AIDUNYAN")) {
        target[c-'A']++;
    }

    string res;
    for(int i = 0; i < str.size(); ++i) {
        cnt[str[i]-'A']++;
        if(i >= 8) cnt[str[i-8]-'A']--;
        if(cnt == target) {
            res = res.substr(0, i-7) + "AIZUNYAN";
        } else {
            res += str[i];
        }
    }
    cout << res << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
