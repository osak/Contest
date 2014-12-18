//Name: Operation of Frequency of Appearance
//Level: 2
//Category: シミュレーション
//Note:

/**
 * 問題文のとおりにシミュレーションする。
 * 出現頻度操作は、各数の出現回数を数えるパスと、全体を変換するパスの2パスに分けると良い。
 *
 * オーダーは不明。
 */
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

bool solve() {
    int N;
    cin >> N;
    if(!N) return false;

    vector<int> v(N);
    for(int i = 0; i < N; ++i) {
        cin >> v[i];
    }
    int ans = 0;
    while(true) {
        vector<int> next(N);
        unordered_map<int,int> freq;
        for(int i : v) {
            freq[i]++;
        }
        for(int i = 0; i < N; ++i) {
            next[i] = freq[v[i]];
        }
        if(next == v) break;
        ++ans;
        next.swap(v);
    }
    cout << ans << endl;
    for(int i = 0; i < N; ++i) {
        if(i > 0) cout << ' ';
        cout << v[i];
    }
    cout << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
