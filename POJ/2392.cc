//Name: Space Elevator
//Level: 2
//Category: 動的計画法,DP
//Note:

/**
 * 最低高度が低いものから順に使っていけばよい。
 * （そうでない場合、適当に並び替えることで条件を満たしたままそのように積み替えられる）
 * 各ブロックを置くときは、直前までのブロックで到達可能な高度から、最大c_i個だけ置ける。
 * これは下からDPしていくことで、O(A)で求められる。
 * ただし、Aは最高到達可能高度(A=40000)である。
 *
 * オーダーはO(K log K + AK)。
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

struct Block {
    int h, a, c;

    bool operator <(const Block &b) const {
        return a < b.a;
    }
};
Block blocks[400];
int dp[40001];

bool solve() {
    int K;
    if(scanf("%d", &K) == EOF) return false;
    for(int i = 0; i < K; ++i) {
        scanf("%d %d %d", &blocks[i].h, &blocks[i].a, &blocks[i].c);
    }
    sort(blocks, blocks+K);
    fill_n(dp, 40001, -1);
    dp[0] = 0;
    for(int j = 0; j < K; ++j) {
        Block block = blocks[j];
        for(int i = 0; i <= block.a; ++i) {
            if(dp[i] != -1) {
                //printf("%d %d\n", K, i);
                dp[i] = 0;
            }
        }
        for(int i = 0; i <= block.a-block.h; ++i) {
            if(dp[i] != -1) {
                const int na = i + block.h;
                const int nc = dp[i] + 1;
                if(nc > block.c) continue;
                if(dp[na] == -1 || dp[na] > nc) dp[na] = nc;
            }
        }
    }
    for(int i = 40000; i >= 0; --i) {
        if(dp[i] != -1) {
            printf("%d\n", i);
            break;
        }
    }
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
