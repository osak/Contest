//Name: Day Count
//Level: 2
//Category: 日付
//Note: 

/**
 * 1年1月0日からの経過日数を求める関数を作ればよい。
 *
 * オーダーは O(1)。
 */
#include <iostream>

using namespace std;

int calc(int y, int m, int d) {
    static const int DAYS[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int ans = 0;
    ans += (y-1) * 365 + (y-1)/4 - (y-1)/100 + (y-1)/400;
    for(int i = 1; i < m; ++i) ans += DAYS[i];
    if(m > 2 && (y%4 == 0 && (y%100 != 0 || y%400 == 0))) ++ans;
    ans += d;
    return ans;
}

bool solve(bool first) {
    int y1, m1, d1, y2, m2, d2;
    cin >> y1 >> m1 >> d1 >> y2 >> m2 >> d2;
    if(y1 < 0 || m1 < 0 || d1 < 0 || y2 < 0 || m2 < 0 || d2 < 0) return false;
    cout << calc(y2, m2, d2) - calc(y1, m1, d1) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) first = false;
    return 0;
}
