//Name: Amusing Numbers
//Level: 5
//Category: 数学,二分探索
//Note:

/*
 * ある数 K より辞書順で小さい数の個数は，桁数 l を固定して考えると
 *   (K の上 l 桁からなる数) - 10^(l-1) + 1
 * となる．
 * なぜなら同じ桁数では数値順比較と辞書順比較が等しくなるからである．
 * たとえば，K = 12345 のとき
 * ・1桁では 1 - 1 + 1 = 1
 * ・2桁では 12 - 10 + 1 = 3 (10, 11, 12)
 * ・3桁では 123 - 100 + 1 = 24 (100, 101, ... 123)
 * 等．
 * また，桁数が K より大きい数では同様にして
 *   (K * 10^(l - Kの桁数)) - 10^(l-1)
 * となる．
 * ここでは (K*10^(l - Kの桁数)) そのものは K より辞書順で大きいため，最後の +1 がないことに注意．
 *
 * ある数 K の位置は 上限 N が増加するに従って広義単調増加になっているので，これを利用して N を二分探索すればよい．
 * 位置が動かない 10^x を除くと最も位置が増加しづらいのは 10^8 + 1 だが，これは Sample Input より 10^17 程度であることがわかる．
 * したがって二分探索の上限は 10^18 程度でよく，unsigned long long に収まる．
 *
 * 計算量は位置の計算が O(log K)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef unsigned long long ULL;

// num <= lim
ULL position_of(ULL num, ULL lim) {
    ULL res = 0;
    ULL ord = 1;
    // num 以下の数で num より前にあるものの個数
    while(ord <= num) {
        ULL tmp = num;
        while(tmp / 10 >= ord) tmp /= 10;
        res += tmp-ord+1;
        ord *= 10;
    }
    // num より上(exclusive) lim 以下の数で num より前にあるものの個数
    while(ord <= lim) {
        ULL tmp = num;
        while(tmp < ord) tmp *= 10;
        res += min(tmp, lim+1)-ord;
        ord *= 10;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ULL K, M;
    cin >> K >> M;

    // (left, right]
    ULL left = K-1, right = 1;
    for(int i = 0; i < 18; ++i) right *= 10;
    bool found = false;
    while(left+1 < right) {
        ULL center = (left+right) / 2;
        //cout << left << ' ' << right << ' ' << center << endl;
        ULL pos = position_of(K, center);
        //cout << pos << endl;
        if(pos >= M) {
            right = center;
            if(pos == M) found = true;
        } else {
            left = center;
        }
    }
    if(found) cout << right << endl;
    else cout << 0 << endl;
    return 0;
}
