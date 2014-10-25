//Name: Search II
//Level: 2
//Category: データ構造,二分探索,練習問題
//Note:

/**
 * 二分木やハッシュテーブルでSに含まれる数を管理する、Sをソートしておいて二分探索である数が含まれるか判定する等の方法がある。
 *
 * ここでは、ハッシュテーブルを使った高速な方法で実装している。
 * オーダーは O(N + Q)。
 */

#include <iostream>
#include <unordered_set>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;

    unordered_set<int> dict;
    for(int i = 0; i < N; ++i) {
        int v;
        cin >> v;
        dict.insert(v);
    }

    int Q;
    cin >> Q;
    int ans = 0;
    for(int i = 0; i < Q; ++i) {
        int q;
        cin >> q;
        ans += dict.count(q);
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
