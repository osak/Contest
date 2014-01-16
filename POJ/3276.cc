//Name: Face The Right Way
//Level: 2
//Category: 動的計画法,DP,貪欲,Greedy
//Note:

/**
 * Kをひとつ決めると、最適な操作は先頭から貪欲に牛をひっくり返していくことで達成できる。
 * Kの値については全探索を行うが、操作回数の計算を愚直にO(NK)かけていると間に合わない。
 * ここで、いもす法のように回転させる範囲の先頭で+1、末尾で-1するようなカウンタを考えると、
 * ある位置でカウンタが奇数のときに限り、その牛を反転させると考えられる。
 *
 * オーダーはO(NK)。
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
    static bool pattern[5000];
    TIMES(i, N) {
        char c;
        scanf(" %c", &c);
        pattern[i] = (c == 'F');
    }
    int ans_k = 0, ans_m = N+1;
    for(int k = 1; k <= N; ++k) {
        static int cnt[5005];
        fill_n(cnt, N+1, 0);
        int m = 0;
        for(int j = 0; j <= N-k; ++j) {
            const bool rev = (cnt[j] % 2 == 1);
            if(!(pattern[j] ^ rev)) {
                cnt[j]++;
                cnt[j+k]--;
                ++m;
            }
            cnt[j+1] += cnt[j];
        }
        bool valid = true;
        for(int j = N-k+1; j < N; ++j) {
            const bool rev = (cnt[j] % 2 == 1);
            if(!(pattern[j] ^ rev)) {
                valid = false;
                break;
            }
            cnt[j+1] += cnt[j];
        }
        if(valid && m < ans_m) {
            ans_k = k;
            ans_m = m;
        }
    }
    printf("%d %d\n", ans_k, ans_m);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
