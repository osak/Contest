//Name: Temperature Difference
//Level: 1
//Category: やるだけ
//Note:

/**
 * 問題文のとおりにやるだけ。
 */
#include <iostream>

using namespace std;

bool solve() {
    for(int i = 0; i < 7; ++i) {
        int a, b;
        cin >> a >> b;
        cout << a-b << endl;
    }
    return false;
}

int main() {

    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
