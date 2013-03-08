//Name: Expected Difference
//Level: 3
//Category: 確率,期待値
//Note:

/*
 * 期待値の線型性より，最小値と最大値の期待値を別々に求めて最後に引けばよい．
 * A_iが最小になる確率は，A_iを選んだ上でそれ以上の数のみでM-1個を取ればよいので
 *   comb(N-i-1, M-1) / comb(N, M)
 * となる．ここでcombはコンビネーション関数である．
 * 分母が変化しないことに着目してこの式を簡約すると，i=0のときにM/Nを取り，
 * iが1増えるごとに(N-M-i)/(N-1-i)倍ずつされていくことが分かる．
 * 最大値については対称性を用いることで，最小値と同時に計算できる．
 *
 * オーダーは O(N)．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<int> as(N);
        for(int i = 0; i < N; ++i) {
            cin >> as[i];
        }

        double prob = static_cast<double>(M) / N;
        double emin = 0, emax = 0;
        for(int i = 0; i <= N-M; ++i) {
            emin += as[i] * prob;
            emax += as[N-i-1] * prob;
            prob *= static_cast<double>(N-M-i) / (N-1-i);
        }
        printf("%.3f\n", emax-emin);
    }
    return 0;
}
