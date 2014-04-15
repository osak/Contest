//Name: Magical Girl Sayaka-chan
//Level: 3
//Category: 動的計画法,DP
//Note:

/**
 * コストのかかり方は、距離s_iの辺で一直線になっているグラフ上を移動する
 * ことと等しいので、円状であることを無視した場合、Kの昇順に並べるのがもっとも効率がよい。
 * しかし、実際には円状であるため、始点と終点では昇順でなくなってしまう。
 * ここで、全体を2つの直鎖に分割することを考えると、それぞれの直鎖ではk_iの昇順に並べるのが最適である。
 * したがって、両者がぶつかる1点以外では昇順にk_iを並べることになるので、コストはDPで計算することができる。
 * （全体を3つ以上の直鎖に分割する場合は、マージして2本の直鎖にできる）
 *
 * オーダーはO(N^2)。
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define TIMES(i_, n_) for(int i_ = 0; i_ < (n_); ++i_)
typedef long long LL;

int N, M, L;
vector<int> ks;
vector<int> ss;
vector<LL> acc;
LL memo[2001][2001];

LL cost(int a, int b) {
    int ka = ks[a];
    int kb = ks[b];
    if(ka > kb) swap(ka, kb);
    return (acc[kb] - acc[ka-1]) / L;
}

LL calc(int l, int r) {
    if(memo[l][r] != -1) return memo[l][r];
    const int next = max(l, r) + 1;
    if(next == N) {
        return cost(l, r);
    }
    memo[l][r] = min(calc(next, r) + cost(l, next), calc(l, next) + cost(r, next));
    return memo[l][r];
}

bool solve() {
    if(!(cin >> N >> M >> L)) return false;
    if(!N && !M && !L) return false;

    ks.resize(N);
    TIMES(i, N) {
        cin >> ks[i];
    }
    ss.resize(M);
    TIMES(i, M) {
        cin >> ss[i];
    }
    acc.resize(M+1);
    acc[0] = 0;
    for(int i = 1; i <= M; ++i) {
        acc[i] = acc[i-1] + ss[i-1];
    }

    sort(ks.begin(), ks.end());
    TIMES(i, N) {
        TIMES(j, N) {
            memo[i][j] = -1;
        }
    }
    cout << calc(0, 0) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
