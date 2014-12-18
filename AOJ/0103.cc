//Name: Baseball Simulation
//Level: 1
//Category: やるだけ
//Note:

/**
 * 仕様のとおりに実装する。
 *
 * オーダーは O(E)。
 * ただし、Eはイベントの個数。
 */
#include <iostream>
#include <string>

using namespace std;

bool solve() {
    int out = 0;
    int b1 = 0, b2 = 0, b3 = 0;
    int score = 0;
    while(out < 3) {
        string event;
        cin >> event;
        if(event == "HIT") {
            if(b3) ++score;
            b3 = b2; b2 = b1; b1 = 1;
        } else if(event == "HOMERUN") {
            score += b1+b2+b3+1;
            b1 = b2 = b3 = 0;
        } else if(event == "OUT") {
            ++out;
        }
    }
    cout << score << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    while(T--) solve();
    return 0;
}
