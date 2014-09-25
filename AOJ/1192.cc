//Name: Tax Rate Changed
//Level: 2
//Category: 全探索
//Note:

/**
 * 2商品の税抜き価格を全探索する。
 * 変更前の消費税は高々100%であるから、税抜き価格は高々2sに収まる。
 * （上限はまじめに計算してもよい）
 *
 * オーダーは O(s^2)。
 */
#include <iostream>
#include <algorithm>

using namespace std;

int calc(int x, int v) {
    return v * (100+x) / 100;
}

bool solve() {
    int x, y, s;
    if(!(cin >> x >> y >> s)) return false;
    if(!x && !y && !s) return false;

    int ans = 0;
    for(int i = 1; i < s*2; ++i) {
        for(int j = 1; j < s*2; ++j) {
            const int s1 = calc(x, i);
            const int s2 = calc(x, j);
            if(s1 + s2 == s) {
                ans = max(ans, calc(y, i) + calc(y, j));
            }
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
