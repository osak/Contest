//Name: Cow Patterns
//Level: 3
//Category: 組み合わせ,ローリングハッシュ
//Note:

/**
 * パターンに出てくるそれぞれの数値について、ローリングハッシュのどの位に出てきたかを覚えておく。
 * これを利用すると、パターンに対するある数値の割り当てを決めたとき、その割り当てのハッシュ値は O(S) で求められる。
 * これをすべて記憶しておき、問題の数列に対してローリングハッシュを求めながら存在判定を行っていく。
 *
 * オーダーはO(C(S,R) + N)。
 * ただしC(,)はコンビネーション、Rはパターン中の数値の種類数。
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

typedef unsigned long long ULL;

const ULL PRIME = 31;
bool exists[26];
ULL sub[26];
ULL cows[100000];
ULL acceptable[5300000];

inline int popcount(unsigned x) {
    x = (x & 0x55555555U) + ((x & 0xaaaaaaaaU) >> 1);
    x = (x & 0x33333333U) + ((x & 0xccccccccU) >> 2);
    x = (x & 0x0f0f0f0fU) + ((x & 0xf0f0f0f0U) >> 4);
    x = (x & 0x00ff00ffU) + ((x & 0xff00ff00U) >> 8);
    x = (x & 0x0000ffffU) + ((x & 0xffff0000U) >> 16);
    return x;
}

bool solve() {
    int N, K, S;
    if(scanf("%d %d %d", &N, &K, &S) == EOF) return false;
    for(int i = 0; i < N; ++i) {
        scanf("%d", cows+i);
    }
    ULL ord = 1;
    int rcnt = 0;
    for(int i = 0; i < K; ++i) {
        int r;
        scanf("%d", &r);
        if(!exists[r]) {
            ++rcnt;
            exists[r] = true;
        }
        sub[r] += ord;
        ord *= PRIME;
    }
    const int lim = 1 << S;
    int cnt = 0;
    for(int pat = 0; pat < lim; ++pat) {
        if(popcount(pat) != rcnt) continue;
        ULL h = 0;
        int idx = 0;
        for(int i = 1; i <= S; ++i) {
            if(pat & (1<<(i-1))) {
                while(!exists[idx]) ++idx;
                h += sub[idx] * i;
                ++idx;
            }
        }
        acceptable[cnt++] = h;
    }
    sort(acceptable, acceptable+cnt);
    ULL cur = 0;
    for(int i = N-1; i >= N-K; --i) {
        cur *= PRIME;
        cur += cows[i];
    }
    //printf("%lld\n", cur);
    vector<int> pos;
    for(int i = N-K-1; i >= -1; --i) {
        if(binary_search(acceptable, acceptable+cnt, cur)) {
            pos.push_back(i+1);
        }
        if(i == -1) break;
        cur *= PRIME;
        cur -= cows[i+K] * ord;
        cur += cows[i];
    }
    reverse(pos.begin(), pos.end());
    printf("%d\n", pos.size());
    for(int i = 0; i < pos.size(); ++i) {
        printf("%d\n", pos[i]+1);
    }
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
