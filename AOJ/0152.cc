//Name: Bowling
//Level: 2
//Category: シミュレーション
//Note: 

/**
 * 倒したピン数を監視しながらフレーム数を管理する。
 * スペアかストライクが出た場合、次以降の投球を見て追加点を決める。
 *
 * オーダーは O(NM + M log M)。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

bool solve(bool first) {
    int M;
    if(!(cin >> M)) return false;
    if(!M) return false;

    cin.ignore();
    vector<pair<int,int>> v;
    while(M--) {
        string line;
        getline(cin, line);
        istringstream is(line);

        int id;
        is >> id;

        vector<int> history;
        int pin;
        while(is >> pin) history.push_back(pin);

        int frame = 1;
        int score = 0;
        int acc = 0, turn = 0;
        for(int i = 0; i < history.size(); ++i) {
            ++turn;
            score += history[i];
            acc += history[i];
            if(frame != 10) {
                if(acc == 10) {
                    if(turn == 1) score += history[i+1] + history[i+2];
                    else if(turn == 2) score += history[i+1];
                    turn = 2;
                }
                if(turn == 2) {
                    ++frame;
                    acc = 0;
                    turn = 0;
                }
            }
        }
        v.emplace_back(-score, id);
    }
    sort(begin(v), end(v));
    for(const auto &p : v) {
        cout << p.second << ' ' << -p.first << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
