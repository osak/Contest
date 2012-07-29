//Name: Ring
//Level: 1
//Category: 文字列，やるだけ
//Note:

/*
 * 指輪は必ず10文字，探す文字列は高々10文字なので指輪の文字列を2つくっつけると
 * 探す文字列が取れるなら必ず出現する．
 */
#include <iostream>
#include <string>

using namespace std;

int main() {
    string need;
    cin >> need;
    int N;
    cin >> N;
    int ans = 0;
    while(N--) {
        string str;
        cin >> str;
        str += str;
        if(str.find(need) != string::npos) ++ans;
    }
    cout << ans << endl;
    return 0;
}
