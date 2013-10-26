//Name: Vase Collection
//Level: 2
//Category: 動的計画法,DP,探索
//Note:

/**
 * 花瓶の数は最大で100個だから、答えは高々10通りであることがわかる。
 *
 * それぞれの花瓶に対して、持っている模様をビットで管理する。
 * これを先頭から順に、使うか使わないかを決めていく。
 * このとき、解に使える模様のパターン数は単調減少していくので、
 * その時点で得られている最大解を実現できなくなった時点で枝刈りする。
 * （これは最初の考察より、個数が10を超えるまでに必ず発生する）
 * こうすることで、探索するパターン数は高々Σ_(1≦i≦10)36_C_i個で抑えられる。
 */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long ULL;

int popcount(ULL v) {
    v = (v & 0x5555555555555555LL) + ((v & 0xaaaaaaaaaaaaaaaaLL) >> 1);
    v = (v & 0x3333333333333333LL) + ((v & 0xccccccccccccccccLL) >> 2);
    v = (v & 0x0f0f0f0f0f0f0f0fLL) + ((v & 0xf0f0f0f0f0f0f0f0LL) >> 4);
    v = (v & 0x00ff00ff00ff00ffLL) + ((v & 0xff00ff00ff00ff00LL) >> 8);
    v = (v & 0x0000ffff0000ffffLL) + ((v & 0xffff0000ffff0000LL) >> 16);
    v = (v & 0x00000000ffffffffLL) + ((v & 0xffffffff00000000LL) >> 32);
    return (int)v;
}

vector<ULL> pat(36);
void solve() {
    int N;
    scanf("%d", &N);
    fill(pat.begin(), pat.end(), 0);
    for(int i = 0; i < N; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        --a; --b;
        pat[a] |= (1LL << b);
    }
    int ans = 0;
    vector<pair<int,ULL> > q[2];
    q[0].push_back(make_pair(0, (1LL<<36)-1));
    for(int i = 0; i < 36; ++i) {
        q[1].clear();
        const int M = q[0].size();
        for(int j = 0; j < M; ++j) {
            const pair<int,ULL> cur = q[0][j];
            if(popcount(cur.second) > ans) q[1].push_back(cur);
            const int np = cur.second & pat[i];
            const int npop = popcount(np);
            if(npop > ans) {
                if(cur.first+1 >= npop) ans = npop;
                q[1].push_back(make_pair(cur.first+1, np));
            }
        }
        q[0].swap(q[1]);
    }
    printf("%d\n", ans);
}

int main() {
    int N;
    scanf("%d", &N);
    while(N--) solve();
    return 0;
}
