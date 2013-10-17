//Name: Matrix
//Level: 3
//Category: データ構造,遅延評価
//Note:

/**
 * ある範囲を一様に更新するクエリを高速に処理するには、Segment Treeなどを使って計算を必要になるまで遅延させたり、
 * いもす法のように累積和を使って表現したりするのが定石。
 * 前者では2次元Segment Tree、後者ではFenwick Treeなどが考えられるが、ここではビット演算を使って高速化する方法を用いた。
 * 各行、各マスごとに更新クエリの境界が来た回数を覚えておき、(x,y)の値が必要になったときは上から順番に境界の数を数え、
 * その偶奇で(x,y)の値が計算できる。
 *
 * オーダーは更新、読み出しともにO(N)。
 * ただし更新にかかるコストが愚直にやるより32倍程度速いため、10ケースくらい来てもTLEにはならない。
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

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

unsigned mask[1001][32];

inline int pos_of(int x) {
    return x / 32;
}

inline unsigned bit_of(int x) {
    return 31 - x%32;
}

void solve() {
    int N, T;
    scanf(" %d %d ", &N, &T);
    TIMES(i, N) {
        TIMES(j, 32) {
            mask[i][j] = 0;
        }
    }

    while(T--) {
        char cmd;
        scanf(" %c", &cmd);
        if(cmd == 'C') {
            int x1, y1, x2, y2;
            scanf(" %d %d %d %d", &x1, &y1, &x2, &y2);
            --x1; --y1; --x2; --y2;
            const int sp1 = pos_of(x1), sp2 = pos_of(x2);
            const int sb1 = bit_of(x1), sb2 = bit_of(x2);
            if(sp1 == sp2) {
                const unsigned m = ((1LL<<(sb1+1))-1) & ~((1<<sb2)-1);
                //printf("%d %d mask: %x\n", sb1, sb2, m);
                mask[y1][sp1] ^= m;
                mask[y2+1][sp2] ^= m;
            } else {
                for(int p = sp1; p <= sp2; ++p) {
                    unsigned m = 0;
                    if(p == sp1) {
                        m = (1LL<<(sb1+1))-1;
                    } else if(p == sp2) {
                        m = ~((1<<sb2)-1);
                    } else {
                        m = ~0;
                    }
                    mask[y1][p] ^= m;
                    mask[y2+1][p] ^= m;
                }
            }
        } else if(cmd == 'Q') {
            int x, y;
            scanf(" %d %d", &x, &y);
            --x; --y;
            const int p = pos_of(x), b = bit_of(x);
            const unsigned m = 1U<<b;
            unsigned res = 0;
            for(int yy = 0; yy <= y; ++yy) {
                res ^= mask[yy][p] & m;
            }
            printf("%d\n", !!res);
        }
    }
    puts("");
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    scanf("%d", &N);
    while(N--) solve();
    return 0;
}
