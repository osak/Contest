//Name: Art of Balance
//Level: 3
//Category: 動的計画法,DP,組み合わせ,数え上げ
//Note:

/**
 * おもりが16個しかない（ノード100個はフェイク）。
 * したがって、各ノードで、それ以下のノードで使えるおもりの組み合わせについて
 * 最も良い結果をメモしておきながら探索すればよい。
 * 組み合わせの列挙にはビット演算を使うとよい。
 *
 * オーダーはO(2^M M^2)。
 */
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>
#include <cmath>

using namespace std;

pair<int,int> tree[101];
int need[101];
double memo[101][1<<16];
int weight[16];
vector<int> comb[17];

inline int popcount(unsigned x) {
    x = (x & 0x55555555U) + ((x & 0xaaaaaaaaU) >> 1);
    x = (x & 0x33333333U) + ((x & 0xccccccccU) >> 2);
    x = (x & 0x0f0f0f0fU) + ((x & 0xf0f0f0f0U) >> 4);
    x = (x & 0x00ff00ffU) + ((x & 0xff00ff00U) >> 8);
    x = (x & 0x0000ffffU) + ((x & 0xffff0000U) >> 16);
    return x;
}

void init() {
    for(unsigned i = 0; i < (1<<16); ++i) {
        const int pc = popcount(i);
        comb[pc].push_back(i);
    }
}

int calc_need(int x) {
    if(tree[x].first == -1) return need[x] = 1;
    return need[x] = calc_need(tree[x].first) + calc_need(tree[x].second);
}

double dfs(int x, unsigned pat) {
    if(tree[x].first == -1) {
        return 0;
    }
    if(memo[x][pat] < 1e9) return memo[x][pat];
    /*
    if(popcount(pat) != need[x]) {
        printf("%x %d %d %d\n", pat, popcount(pat), need[x], x);
        assert(false);
    }
    */
    const int nl = need[tree[x].first];
    const int K = comb[nl].size();
    const unsigned lim = 1<<popcount(pat);
    //printf("%d %d\n", x, popcount(pat));
    for(int i = 0; i < K; ++i) {
        const int cp = comb[nl][i];
        if(cp >= lim) break;
        //printf("%x %x\n", pat, cp);
        unsigned lp = 0, rp = 0;
        unsigned cmask = 1;
        int lw = 0, rw = 0;
        int widx = 0;
        unsigned ptmp = pat;
        while(ptmp) {
            while(!(ptmp & 1)) {
                ptmp >>= 1;
                widx++;
            }
            if(cp & cmask) {
                lp |= 1<<widx;
                lw += weight[widx];
            } else {
                rp |= 1<<widx;
                rw += weight[widx];
            }
            ptmp >>= 1;
            widx++;
            cmask <<= 1;
        }
        const double net = dfs(tree[x].first, lp) + dfs(tree[x].second, rp);
        memo[x][pat] = min(memo[x][pat], net + fabs(500-1000.0*lw/(lw+rw)));
    }
    return memo[x][pat];
}

void solve() {
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        tree[i+1].first = a;
        tree[i+1].second = b;
        for(unsigned j = 0; j < (1<<16); ++j) {
            memo[i+1][j] = 1e10;
        }
    }
    int M;
    scanf("%d", &M);
    for(int i = 0; i < M; ++i) {
        scanf("%d", weight+i);
    }
    calc_need(1);
    double ans = dfs(1, (1<<M)-1);
    printf("%.3f\n", ans);
}

int main() {
    init();
    int N;
    scanf("%d", &N);
    while(N--) solve();
    return 0;
}
