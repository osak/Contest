//Name: Bullseye
//Level: 1
//Category: 幾何,やるだけ
//Note:

/*
 * 距離計算やるだけ．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)

int score(double x, double y) {
    double len = hypot(x, y);
    if(len <= 3.0) return 100;
    else if(len <= 6.0) return 80;
    else if(len <= 9.0) return 60;
    else if(len <= 12.0) return 40;
    else if(len <= 15.0) return 20;
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        int score1 = 0, score2 = 0;
        for(int i = 0; i < 3; ++i) {
            double x, y;
            cin >> x >> y;
            if(i == 0 && x == -100) return 0;
            score1 += score(x, y);
        }
        for(int i = 0; i < 3; ++i) {
            double x, y;
            cin >> x >> y;
            score2 += score(x, y);
        }
        cout << "SCORE: " << score1 << " to " << score2 << ", ";
        if(score1 == score2) {
            cout << "TIE." << endl;
        } else {
            cout << "PLAYER " << (score1>score2?1:2) << " WINS." << endl;
        }
    }
    return 0;
}
