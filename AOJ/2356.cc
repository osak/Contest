//Name: Palindromic Anagram
//Level: 2
//Category: 文字列,回文,数え上げ
//Note:

/**
 * 回文は、それぞれの文字について個数を数え、
 * ・文字列長が奇数であれば、ちょうど1種類の文字が奇数個
 * ・文字列長が偶数であれば、すべての文字が偶数個
 * であれば構成できる。
 *
 * あとは、片側の並べ方だけを考えればよく、これは重複順列を計算すれば求められる。
 * オーダーは O(|S|)。
 */
#include <iostream>
#include <string>
#include <map>

using namespace std;

typedef unsigned long long ULL;

int main() {
    string str;
    cin >> str;
    int S = str.size();

    map<char, int> cnt;
    for(int i = 0; i < str.size(); ++i) {
        cnt[str[i]]++;
    }

    ULL ans = 0;
    int odd = 0;
    char oddchar = '\0';
    for(map<char,int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
        if(it->second % 2 == 1) {
            ++odd;
            oddchar = it->first;
        }
    }

    if((S%2 == 0 && odd > 0) || (S%2 == 1 && odd != 1)) {
        goto end;
    }
    if(odd) {
        cnt[oddchar]--;
    }

    S &= ~1;
    ans = 1;
    for(int i = 1; i <= S/2; ++i) ans *= i;
    for(map<char,int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
        for(int j = 1; j <= it->second/2; ++j) {
            ans /= j;
        }
    }

end:
    cout << ans << endl;
    return 0;
}
