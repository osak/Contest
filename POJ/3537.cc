//Name: Crosses and Crosses
//Level: 3
//Category: Grundy数
//Note:

/**
 * xから2マス以内にもうひとつxを置くと次のターンで勝たれてしまうことがわかる。
 * したがって、xを置くごとに盤面は左右に分断されていく（場所によっては片方しか残らない）。
 * このとき、どんな手を打っても敗北するという意味で、Grundy数0を敗北とすると、
 * 幅0のときGrundy数0、幅1のときGrundy数1……とできる。
 * これは、一般的に幅lのとき、場所xで分断した後で左右のGrundy数をxorしたものをl_xとすると、
 * l_xとして実現できない最小の整数がlに対応するGrundy数になる。
 * 実際、これがGrundy数の定理を満たすことは容易に確かめられる。
 *
 * オーダーは前計算にO(L^2)、出力にO(1)。
 * ただし、Lは盤面の最大値(L = 2000)。
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

int grundy[2001];

void init() {
    grundy[0] = 0;
    grundy[1] = 1;
    grundy[2] = 1;
    grundy[3] = 1;
    for(int len = 4; len <= 2000; ++len) {
        static bool can_make[2001];
        fill_n(can_make, 2001, false);
        for(int x = 0; x <= len/2; ++x) {
            const int left = max(0, x-2);
            const int right = max(0, len-(x+3));
            const int next = grundy[left] ^ grundy[right];
            can_make[next] = true;
        }
        TIMES(i, 2001) {
            if(!can_make[i]) {
                grundy[len] = i;
                break;
            }
        }
    }
}

bool solve() {
    int N;
    if(scanf("%d", &N) == EOF) return false;
    puts(grundy[N] == 0 ? "2" : "1");
    return true;
}

int main() {
    init();
    while(solve()) ;
    return 0;
}
