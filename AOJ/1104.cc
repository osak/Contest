//Name: Where's Your Robot?
//Level: 1
//Category: シミュレーション,練習問題
//Note:

/**
 * 問題文の通りにシミュレーションする。
 */
#include <iostream>
#include <string>

using namespace std;

const int DR[] = {1, 0, -1, 0};
const int DC[] = {0, -1, 0, 1};

bool solve() {
    int W, H;
    if(!(cin >> W >> H)) return false;
    if(!W && !H) return false;

    int r = 1, c = 1, dir = 0;
    while(true) {
        string cmd;
        cin >> cmd;
        if(cmd == "FORWARD") {
            int d;
            cin >> d;
            r = max(1, min(H, r + DR[dir] * d));
            c = max(1, min(W, c + DC[dir] * d));
        } else if(cmd == "BACKWARD") {
            int d;
            cin >> d;
            r = max(1, min(H, r - DR[dir] * d));
            c = max(1, min(W, c - DC[dir] * d));
        } else if(cmd == "RIGHT") {
            dir = (dir + 3) % 4;
        } else if(cmd == "LEFT") {
            dir = (dir + 1) % 4;
        } else if(cmd == "STOP") {
            break;
        }
    }
    cout << c << ' ' << r << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
