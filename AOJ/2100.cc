//Name: Saizo
//Level: 1
//Category: やるだけ
//Note:

/**
 * 入力を舐めながら、増加と減少それぞれについて最大値を管理する。
 *
 * オーダーは O(N)。
 */
#include <iostream>
#include <algorithm>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;

    int prev = 0;
    int ansup = 0, ansdown = 0;
    for(int i = 0; i < N; ++i) {
        int h;
        cin >> h;
        if(i > 0) {
            const int d = h - prev;
            if(d > 0) ansup = max(ansup, d);
            else ansdown = max(ansdown, -d);
        }
        prev = h;
    }
    cout << ansup << ' ' << ansdown << endl;
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
