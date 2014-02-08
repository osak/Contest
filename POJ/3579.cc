//Name: Median
//Level: 3
//Category: 二分探索
//Note:

/**
 * 中央値Mを二分探索で見つける。
 * 与えられた数列をソートしておくと、あるx_iに対してjが存在し、k ≧ j → x_k - x_j ≧ M を満たす。
 * このようなjは二分探索で発見することができる。
 *
 * これを利用することで、値Mを決めたとき、M以上である項の個数が高速に求められる。
 * 中央値に対しては、このような項の個数は N(N-1) / 4 + 1 個となる。
 *
 * オーダーはO(N (log N)^2)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

bool solve() {
    int N;
    if(scanf("%d", &N) == EOF) return false;
    if(!N) return false;

    const int TARGET = N*(N-1) / 2 / 2 + 1;
    static int buf[100000];
    TIMES(i, N) {
        scanf("%d", &buf[i]);
    }
    sort(buf, buf+N);
    int left = 0, right = 1000000000;
    while(left+1 < right) {
        const int center = (left+right) / 2;
        int cnt = 0;
        TIMES(i, N) {
            const int d = lower_bound(buf, buf+N, buf[i]+center) - buf;
            cnt += N - d;
        }
        //printf("%d %d\n", center, cnt);
        if(cnt >= TARGET) {
            left = center;
        } else {
            right = center;
        }
    }
    printf("%d\n", left);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
