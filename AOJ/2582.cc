//Name: Step Aerobics
//Level: 1
//Category: やるだけ
//Note:

/**
 * 以下の4パターンのみが正常な踏み台昇降である。
 * ・lu -> ru
 * ・ru -> lu
 * ・ld -> rd
 * ・rd -> ld
 * これらの出現数を数えればよい。
 *
 * オーダーは O(N)。
 */
#include <iostream>
#include <string>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    string prev = "";
    int ans = 0;
    for(int i = 0; i < N; ++i) {
        string cmd;
        cin >> cmd;
        if((prev == "lu" && cmd == "ru") ||
           (prev == "ru" && cmd == "lu") ||
           (prev == "ld" && cmd == "rd") ||
           (prev == "rd" && cmd == "ld")) {
            ++ans;
        }
        prev = cmd;
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
