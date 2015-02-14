//Name: Clock Short Hand and Long Hand
//Level: 2
//Category: 数学
//Note: 

/**
 * 2PI = 1としてから全体を720倍すると、整数のみで計算できる。
 */
#include <iostream>
#include <algorithm>

using namespace std;

bool solve(bool first) {
    int H, M;
    cin >> H;
    cin.ignore();
    cin >> M;

    //const double ha = 2*PI * (H/12 + M/12/60);
    //const double ma = 2*PI * M/60;
    const int ha = 60*H + M;
    const int hb = 12*M;
    const int diff = min(abs(ha-hb), abs(720-abs(ha-hb)));
    if(diff < 60) {
        cout << "alert" << endl;
    } else if(diff >= 180) {
        cout << "safe" << endl;
    } else {
        cout << "warning" << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    int N;
    cin >> N;
    while(N-- && solve(first)) {
        first = false;
    }
    return 0;
}
