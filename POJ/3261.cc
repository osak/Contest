//Name: Milk Patterns
//Level: 3
//Category: Suffix Array
//Note: パターンは連続して出現する必要はない

/**
 * Suffix Arrayの構築途中でできる、長さ1, 2, 4, 8, ...の同値類表を使うことで
 * 特定の長さについての同値類表が作成できる。
 * 大きさがK以上の同値類を作るような長さについて、二分探索を行えば良い。
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

// ord_of[i] = order by comparing first 2^i chars
int ord_of[16][20000];

struct Cmp {
    int lv;
    int N;
    int *arr;
    Cmp(int lv, int N, int *arr) : lv(lv), N(N), arr(arr) {}

    bool operator ()(const int a, const int b) const {
        if(lv == 0) return arr[a] < arr[b];
        if(ord_of[lv-1][a] != ord_of[lv-1][b]) return ord_of[lv-1][a] < ord_of[lv-1][b];
        const int na = a + (1<<(lv-1));
        const int nb = b + (1<<(lv-1));
        if(na >= N && nb >= N) return ord_of[lv-1][a] < ord_of[lv-1][b];
        else if(na >= N) return true;
        else if(nb >= N) return false;
        return ord_of[lv-1][na] < ord_of[lv-1][nb];
    }
};

struct Cmp2 {
    int len;
    int N;
    int max_lv;
    Cmp2(int len, int N, int max_lv) : len(len), N(N), max_lv(max_lv) {}

    bool operator()(const int a, const int b) const {
        if(a + len > N || b + len > N) return ord_of[max_lv][a] < ord_of[max_lv][b];
        int offset = 0;
        for(int lv = 0; offset < len; ++lv) {
            if(len & (1<<lv)) {
                const int na = a + offset;
                const int nb = b + offset;
                if(ord_of[lv][na] != ord_of[lv][nb]) return ord_of[lv][na] < ord_of[lv][nb];
                offset += (1<<lv);
            }
        }
        return false;
    }
};

int build(int *arr, int N) {
    static int sa[20000];
    TIMES(i, N) {
        sa[i] = i;
    }
    int lv = 0;
    while(true) {
        Cmp cmp(lv, N, arr);
        stable_sort(sa, sa+N, cmp);
        TIMES(i, N) {
            ord_of[lv][sa[i]] = i > 0 ? ord_of[lv][sa[i-1]] : 0;
            if(i > 0 && cmp(sa[i-1], sa[i])) {
                ord_of[lv][sa[i]]++;
            }
        }
        if((1<<lv) >= N) break;
        ++lv;
    }
    return lv;
}

bool solve() {
    int N, K;
    if(scanf("%d %d", &N, &K) == EOF) return false;
    if(!N && !K) return false;
    static int arr[20001];
    TIMES(i, N) {
        scanf("%d", arr+i);
    }
    arr[N] = -1;
    const int max_lv = build(arr, N);
    /*
    printf("%d\n", max_lv);
    TIMES(i, 15) {
        TIMES(j, N) {
            printf("%d ", ord_of[i][j]);
        }
        puts("");
    }
    */

    static int sa[20000];
    int ans = 0;
    for(int lv = max_lv; lv >= 0; --lv) {
        TIMES(i, N) {
            sa[i] = i;
        }
        const int len = ans + (1<<lv);
        if(len > N) continue;
        Cmp2 cmp2(len, N, max_lv);
        stable_sort(sa, sa+N, cmp2);
        /*
        printf("%d\n", len);
        TIMES(i, N) {
            printf("%d ", sa[i]);
        }
        puts("");
        */
        int acc = 0;
        TIMES(i, N) {
            if(i > 0 && cmp2(sa[i-1], sa[i])) {
                acc = 0;
            }
            /*
            if(sa[i-1]+len < sa[i]) {
                acc = 0;
            }
            */
            if(++acc == K) break;
        }
        if(acc == K) {
            ans = len;
        }
    }
    printf("%d\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
