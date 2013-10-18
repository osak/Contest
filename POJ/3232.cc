//Name: Accelerator
//Level: 3
//Category: 最小化,minimize,二分探索
//Note: ブースターを使った時間に進む距離は、KではなくK+1である。

/**
 * 最大値の最小化問題なので、時間tでゴールできるかどうかを、tで二分探索しながら判定する。
 * プレイヤーiが時間t以下でゴールするためには、最低でもbi = ceil((Ai-t) / (K-1))回のブーストが必要になる。
 * このとき、
 * ・bi ≦ t
 * ・Σbi ≦ M×t
 * の両方が満たされていれば、このようなブースターの配布方法が存在する。
 * M×tはintに収まるとは限らないことに注意する。
 *
 * オーダーはO(N log A)。
 * ただし、A = max Ai。
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

void solve() {
    int N;
    scanf("%d", &N);
    int as[N];
    TIMES(i, N) {
        scanf("%d", as+i);
    }
    int M, K;
    scanf("%d %d", &M, &K);

    if(K == 1) {
        printf("%d\n", *max_element(as, as+N));
    } else {
        --K;
        // Can: (left, right]
        int left = 0, right = *max_element(as, as+N);
        while(left+1 < right) {
            const long long t = (left+right) / 2;
            const long long lim = M*t;
            long long need = 0;
            TIMES(i, N) {
                if(as[i] > t) {
                    const long long tmp = (as[i]-t+K-1) / K;
                    if(tmp > t) {
                        need = lim+1;
                        break;
                    } else {
                        need += tmp;
                    }
                }
            }
            if(need <= lim) {
                right = t;
            } else {
                left = t;
            }
        }
        printf("%d\n", right);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    scanf("%d", &N);
    while(N--) solve();
    return 0;
}
