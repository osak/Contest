//Name: Flow Layout
//Level: 2
//Category: シミュレーション
//Note:

/**
 * 現在置いている行の幅とy座標を覚えておくと、次の矩形を置けるかの判定と、改行したときの位置の計算ができる。
 *
 * オーダーはO(N)。
 * ただしNは矩形の個数。
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
    int W;
    scanf("%d", &W);
    if(!W) return false;

    int acc_w = 0, acc_h = 0;
    int cur_w = 0, cur_y = 0;
    while(true) {
        int w, h;
        scanf("%d %d", &w, &h);
        if(w == -1 && h == -1) break;
        int next_w = cur_w + w;
        if(next_w > W) {
            next_w = w;
            cur_y = acc_h;
        }
        cur_w = next_w;
        acc_w = max(acc_w, cur_w);
        acc_h = max(acc_h, cur_y + h);
    }
    printf("%d x %d\n", acc_w, acc_h);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
