//Name: Monthly Expense
//Level: 2
//Category: 二分探索,貪欲,Greedy
//Note:

/**
 * 求める最大値について二分探索する。
 * 最大値が決まったら、初日から貪欲にfajomonthに入れていき、オーバーしたら繰り上げることを繰り返せば
 * 必要な最低月数が求められる。
 *
 * オーダーは O(N log S)。
 * ただしSは入力の合計値。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

bool solve() {
    int N, M;
    if(scanf("%d %d", &N, &M) == EOF) return false;
    if(!N && !M) return false;

    static int v[100000];
    TIMES(i, N) {
        scanf("%d", &v[i]);
    }
    int left = *max_element(v, v+N)-1, right = accumulate(v, v+N, 0);
    while(left+1 < right) {
        const int lim = (left+right) / 2;
        int cnt = 1;
        int sum = 0;
        TIMES(i, N) {
            if(sum + v[i] > lim) {
                ++cnt;
                sum = v[i];
            } else {
                sum += v[i];
            }
        }
        if(cnt <= M) right = lim;
        else left = lim;
    }
    printf("%d\n", right);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
