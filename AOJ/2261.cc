//Name: [[iwi]]
//Level: 2
//Category: 文字列,全探索
//Note:

/**
 * 文字列長が短いので、使う文字の組み合わせを全通り試す。
 *
 * オーダーは O(2^|S|)。
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

bool solve() {
    string s;
    if(!(cin >> s)) return false;

    int iwi = 0;
    for(int i = 0; i < s.size(); ++i) {
        if(s[i] == 'i' || s[i] == 'w') {
            iwi |= (1<<i);
        }
    }

    unordered_map<char,char> dict;
    dict['i'] = 'i';
    dict['w'] = 'w';
    dict['('] = ')';
    dict[')'] = '(';
    dict['{'] = '}';
    dict['}'] = '{';
    dict['['] = ']';
    dict[']'] = '[';

    int ans = 0;
    const int P = (1 << s.size());
    vector<int> buf;
    for(int i = 0; i < P; ++i) {
        const int pat = i | iwi;
        buf.clear();
        for(int j = 0; j < s.size(); ++j) {
            if(pat & (1<<j)) {
                buf.push_back(j);
            }
        }
        int l = 0, r = (int)buf.size()-1;
        while(l <= r) {
            if(dict[s[buf[l]]] != s[buf[r]]) goto next;
            l++;
            r--;
        }
        ans = max(ans, (int)buf.size());
next:
        ;
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
