//Name: Finding the Largest Carbon Compound Given Its Long
//Level: 4
//Category: 組み合わせ
//Note:

/*
 * 最長部分Nの鎖を作るには，まずN個の炭素を1列に並べ，そこに枝を生やしていく．
 * i番目(1-origin)の炭素に枝を生やすとき，その枝をどのように辿っても根の炭素にたどりついた時に長さが min(i, N-i) でなければならない．
 * (そうしないと最長部分がNより長くなってしまう)
 * これを満たすようにするには，まず炭素1つぶん枝を伸ばし，次にその回りに3つ炭素を置き，次にそれぞれの回りに3つづつ炭素を置き……とすればよい．
 *
 * 最長部分Nの分子を作るときの最大炭素個数をdp[N]で覚えておき，i番目の炭素にはdp[min(i, N-i)]をふたつくっつける，という方法は失敗する．
 * なぜなら最長鎖の制約はどちらの端を端点とした時にも効くが，他の炭素鎖にくっつけると，くっつけたのと逆側に対する制約は意味をなくすからである．
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> ans(31, 0);

    ans[0] = 0;
    for(int i = 1; i <= 30; ++i) {
        ans[i] = i;
        for(int j = 1; j < i-1; ++j) {
            int level = min(j, i-j-1);
            int x = 1;
            for(int k = 0; k < level; ++k) {
                ans[i] += 2*x;
                x *= 3;
            }
        }
    }

    int N;
    while(cin >> N) {
        cout << ans[N] << endl;
    }
    return 0;
}
