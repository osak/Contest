//Name: Backward Digit Sums
//Level: 1
//Category: 動的計画法,DP
//Note:

/**
 * 最初の列に置いた数は、合計値に対して二項係数の重みで影響する。
 * 二項係数を前計算しておき、並びを全探索する。
 *
 * オーダーはO(N^2 + N!)。
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

int coef[10][10];

void init() {
    coef[0][0] = 1;
    TIMES(i, 9) {
        TIMES(j, i+2) {
            coef[i+1][j] = (j > 0 ? coef[i][j-1] : 0) + coef[i][j];
        }
    }
}

bool solve() {
    int N, S;
    if(scanf("%d %d", &N, &S) == EOF) return false;
    static int arr[10];
    TIMES(i, N) {
        arr[i] = i+1;
    }
    do {
        int sum = 0;
        TIMES(i, N) {
            sum += coef[N-1][i] * arr[i];
        }
        if(sum == S) break;
    } while(next_permutation(arr, arr+N));
    TIMES(i, N) {
        if(i > 0) printf(" ");
        printf("%d", arr[i]);
    }
    return true;
}

int main() {
    init();
    while(solve()) ;
    return 0;
}
