//Name: The Great Summer Contest
//Level: 3
//Category: 数学,Math,場合分け
//Note:

/*
 * MathとDP、GreedyとGraph、GeometryとOtherはそれぞれあらかじめ合計したものについて考えてよい。
 * このとき、1〜3の各セットについては、最大でfloor(そのカテゴリの問題数 / 3)個のコンテストが作れる。
 * このようにして可能な限りコンテストを作った後、残った問題数のパターンは
 * (0,0,0), (0,0,1), (0,0,2), (0,1,1), (0,1,2), (0,2,2), (1,1,1), (1,1,2), (1,2,2), (2,2,2)
 * の10通りになる。
 *
 * 上記のパターンのうち、合計が3に満たないものは明らかに最適な配分をしている。
 * 合計が3以上になるもののうち、(0,1,2)と(0,2,2)以外はパターン4のセットを作ることによって最適な配分になる。
 * (0,1,2)の場合は、「どれかのカテゴリに3を足す」「全カテゴリから1を引く」の繰り返しのみでは、mod 3で(0,1,2)以外のパターンを作れないため、これが最適である。
 * (0,2,2)の場合は、0になっているカテゴリに3問以上の問題が存在していた場合は、(3,2,2)としてからパターン4を2つ作ることで最適になる。
 *
 * オーダーは O(1)。
 */
#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

bool solve() {
    array<int,3> ns;
    fill(begin(ns), end(ns), 0);

    for(int i = 0; i < 6; ++i) {
        int v;
        cin >> v;
        ns[i % 3] += v;
    }
    if(all_of(begin(ns), end(ns), [](int a){return a==0;})) return false;

    int ans = ns[0] / 3 + ns[1] / 3 + ns[2] / 3;
    const int mod_sum = ns[0] % 3 + ns[1] % 3 + ns[2] % 3;
    const int mod_pat = (1 << (ns[0]%3)) | (1 << (ns[1]%3)) | (1 << (ns[2]%3));
    if(mod_sum >= 3) {
        if(mod_pat == 0x07) { // (0,1,2)
            // Nothing to do
        } else if(mod_pat == 0x05) { // (0,2,2)
            if((ns[0] % 3 == 0 && ns[0] >= 3) || (ns[1] % 3 == 0 && ns[1] >= 3) || (ns[2] % 3 == 0 && ns[2] >= 3)) {
                ++ans;
            }
        } else {
            ans += mod_sum / 3;
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
