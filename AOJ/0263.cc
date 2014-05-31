//Name: Beat Panel
//Level: 2
//Category: 動的計画法,DP
//Note:

/**
 * jubeatと思いきや、押すまでパネルが消えない仕様になっている。
 * 状態は高々2^16しかないので、各状態で全ての押し方を試せばよい。
 *
 * オーダーは O(NC 2^X)。
 * ただしXはパネルの枚数でX=16。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int popcount(unsigned i) {
    i = ((i & 0xaaaaaaaa) >> 1) + (i & 0x55555555);
    i = ((i & 0xcccccccc) >> 2) + (i & 0x33333333);
    i = ((i & 0xf0f0f0f0) >> 4) + (i & 0x0f0f0f0f);
    i = ((i & 0xff00ff00) >> 8) + (i & 0x00ff00ff);
    i = ((i & 0xffff0000) >> 16) + (i & 0x0000ffff);
    return i;
}

bool solve() {
    int N, C;
    if(!(cin >> N >> C)) return false;
    if(!N &&! C) return false;

    vector<int> patterns(N), press_patterns(C);
    for(int i = 0; i < N; ++i) {
        int v = 0;
        for(int j = 0; j < 16; ++j) {
            int b;
            cin >> b;
            v <<= 1;
            v += b;
        }
        patterns[i] = v;
    }
    for(int i = 0; i < C; ++i) {
        int v = 0;
        for(int j = 0; j < 16; ++j) {
            int b;
            cin >> b;
            v <<= 1;
            v += b;
        }
        press_patterns[i] = v;
    }

    vector<int> memo[2];
    memo[0].resize(1<<16, -1);
    memo[1].resize(1<<16, -1);
    memo[0][0] = 0;
    for(int pat : patterns) {
        fill(memo[1].begin(), memo[1].end(), -1);
        for(int prev = 0; prev < (1<<16); ++prev) {
            if(memo[0][prev] == -1) continue;
            const int cur = pat | prev;
            for(int press : press_patterns) {
                const int np = cur & (~press);
                const int ns = memo[0][prev] + popcount(cur & press);
                memo[1][np] = max(memo[1][np], ns);
            }
        }
        memo[0].swap(memo[1]);
    }
    cout << *max_element(memo[0].begin(), memo[0].end()) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
