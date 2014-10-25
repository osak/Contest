//Name: Search
//Level: 2
//Category: 二分探索,シミュレーション
//Note:

/**
 * 問題文の通りに二分探索を実装し、比較回数を数える。
 *
 * オーダーは O(log N)。
 */

#include <iostream>
#include <vector>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<int> v(N);
    for(int i = 0; i < N; ++i) {
        cin >> v[i];
    }

    int Q;
    cin >> Q;
    int ans = 0;
    int l = 0, r = N-1;
    while(l <= r) {
        const int m = (l+r) / 2;
        ++ans;
        if(v[m] == Q) {
            break;
        } else if(v[m] < Q) {
            l = m+1;
        } else {
            r = m-1;
        }
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
