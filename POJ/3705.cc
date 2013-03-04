//Name: Reverse
//Level: 4
//Category: 数学,Special Judge
//Note:

/*
 * 数列に含まれる減少部分列の個数を考える．
 * たとえば 1 2 3 4 5 6 では減少部分列は6個，3 2 1 6 5 4 では2個ある．
 * このとき，数列から部分列を取り出して移動するという操作では，減少部分列の個数は
 * 高々2個しか減らない．
 * なぜなら，減少部分列が減るパターンは
 * ・(a ... b c) (d e ... f) の間がなくなり， (a ... b e ... f) のようになる (-1)
 * ・(a ... b) (e ... f) の間に減少部分列 (c ...) (... d) が入り，
 *   (a ... b c ...) (... d e ... f) のようになる (-2，片側だけで発生すると-1)
 * しか存在しないためである．
 * 初期状態では減少部分列の個数はNであったものが，最終状態では1になるため，減少部分列はN-1個減らす必要がある．
 * ここで，初手では2つめのパターンの-2が発生し得ないため，減少部分列は1個しか減らない．
 * また，対称性から最終手でも同じことが言える．
 * したがって，手数の下限は
 *   2 + ceil((N-3)/2) = 1 + ceil((N-1)/2)
 * となる．
 *
 * 実際，この下限ちょうどの手数をもつ操作列が構成可能である．
 * 方針としては，(N/2 ... 1) (N ... N/2+1) の数列を外側から構成していくようにすればよい．
 *     1 2 3 4 5 6
 *   →3 4 1 2 5 6
 *   →3 2 5 4 1 6
 *   →3 2 1 6 5 4
 *   →6 5 4 3 2 1
 * こうすると，毎回減少列の個数が2ずつ減っていくことが分かる．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    while(cin >> N) {
        if(N == 1) {
            cout << 0 << endl;
        } else if(N == 2) {
            cout << 1 << endl;
            cout << "1 1 1" << endl;
        } else {
            cout << 1+N/2 << endl;
            int left = (N+1)/2;
            for(int i = 1; i <= N/2; ++i) {
                cout << left << ' ' << 2 << ' ' << i-1 << endl;
                ++left;
            }
            // Last step
            cout << N/2+1 << ' ' << N/2 << ' ' << 0 << endl;
        }
    }
    return 0;
}
