//Name: Olympiad
//Level: 3
//Category: 組み合わせ,貪欲,Greedy
//Note: Codeforces #137

/*
 * 最大値どうしを足すことで1位が上限であることは容易に分かる．
 * 問題は順位の下限だが，これは和がX以上になる数値の組がいくつできるかを見ればよい．
 * 両方の数列をソートし，片方は小さい方から，もう片方は大きい方から対応付けていく．
 * (あるa[i]に対してa[i]+b[j]>=Xとなるとき，j'>jとなるj'もこれを満たすことから
 *  小さいa[i]に対しては大きいb[j]を割り当てていくとよい)
 */
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int as[100000], bs[100000];

int main() {
    int N, X;
    scanf("%d %d", &N, &X);
    for(int i = 0; i < N; ++i) {
        scanf("%d", as+i);
    }
    for(int i = 0; i < N; ++i) {
        scanf("%d", bs+i);
    }
    sort(as, as+N);
    sort(bs, bs+N);
    int ans = 0;
    int p = 0, q = N-1;
    for(p = 0; p < N; ++p) {
        if(as[p]+bs[q] >= X) {
            ++ans;
            --q;
        }
    }
    cout << 1 << ' ' << ans << endl;
    return 0;
}
