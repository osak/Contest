//Name: Ticket Sales
//Level: 1
//Category: やるだけ
//Note:

/**
 * t_iからチケット1枚あたりの値段を求められれば良い。
 * 配列やif文などでやるだけ。
 */
#include <iostream>

using namespace std;

bool solve() {
    const int PRICE[] = {6000, 4000, 3000, 2000};
    for(int i = 0; i < 4; ++i) {
        int t, n;
        cin >> t >> n;
        cout << PRICE[t-1]*n << endl;
    }
    return false;
}

int main() {

    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
