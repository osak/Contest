//Name: Osaki
//Level: 2
//Category: 区間,区間の重なり,累積和
//Note: 

/**
 * 少し問題文がわかりづらいが、与えられた区間が最も多く重なっているとき、いくつの区間が重なっているかを答える問題。
 * 1日の1秒を1要素に対応させた配列を用意して、各区間について出発時に+1、到着時に-1を書き込み、累積和を取った時に
 * 配列内の最大値が求める答えである。
 *
 * オーダーは O(N + S)。
 * ただしSは1日の秒数で、S=86400。
 */
#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

int read_time() {
    int h, m, s;
    cin >> h;
    cin.ignore();
    cin >> m;
    cin.ignore();
    cin >> s;
    return h*3600 + m*60 + s;
}

bool solve(bool first) {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    static array<int,86400> v;
    fill(begin(v), end(v), 0);
    for(int i = 0; i < N; ++i) {
        const int s = read_time();
        const int t = read_time();
        v[s]++;
        v[t]--;
    }
    int ans = 0;
    for(int i = 1; i < 86400; ++i) {
        v[i] += v[i-1];
        ans = max(ans, v[i]);
    }
    cout << ans << endl;
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
