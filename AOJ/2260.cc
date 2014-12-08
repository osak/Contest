//Name: (iwi)
//Level: 2
//Category: 文字列,アドホック,Ad-hoc,貪欲法,Greedy
//Note:

/**
 * 文字列を両端から読んでいき、線対称になっていなければどちらか片方を変更すればよい。
 *
 * オーダーは O(|S|)。
 */
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

bool solve() {
    string s;
    if(!(cin >> s)) return false;

    int l = 0, r = (int)s.size()-1;
    int ans = 0;
    while(l <= r) {
        if((s[l] == 'i' && s[r] == 'i') ||
           (s[l] == 'w' && s[r] == 'w') ||
           (s[l] == '(' && s[r] == ')') ||
           (s[l] == ')' && s[r] == '(')) {
        } else {
            ans++;
        }
        l++;
        r--;
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
