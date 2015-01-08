//Name: Candy and Class Flag
//Level: 1
//Category: やるだけ
//Note: 

/**
 * 剰余を取ればよい。
 *
 * オーダーは O(1)。
 */
#include <iostream>

using namespace std;

bool solve(bool first) {
    int N;
    if(!(cin >> N)) return false;

    cout << "3C";
    cout.width(2);
    cout.fill('0');
    cout << ((N-1)%39+1) << endl;
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
