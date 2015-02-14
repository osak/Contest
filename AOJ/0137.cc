//Name: Middle-Square Method
//Level: 1
//Category: やるだけ
//Note: 

/**
 * 8桁の数の中央4桁は、100で割ってから10000で剰余を取れば求められる。
 */
#include <iostream>
#include <algorithm>

using namespace std;

void solve(int CASE) {
    int N;
    cin >> N;
    cout << "Case " << CASE << ":" << endl;
    for(int i = 0; i < 10; ++i) {
        N *= N;
        N = N / 100 % 10000;
        cout << N << endl;
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    int N;
    cin >> N;
    for(int i = 0; i < N; ++i) {
        solve(i+1);
    }
    return 0;
}
