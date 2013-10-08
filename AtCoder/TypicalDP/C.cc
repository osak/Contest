//Name: トーナメント
//Level: 3
//Category: DP,動的計画法
//Note: Typical DP Contest C

/**
 * 人iが第kラウンドに進出できる確率をDPする。
 *   dp[k][i] = ∑ dp[k-1][j] * win_prob(i, j)
 * ただし、jは第kラウンドで人iが対戦し得る相手である。
 * これは、トーナメント表の性質から、人iのk-th LSBを反転し、
 * kビット目以降を全パターン網羅したものによって得られる。
 *
 * オーダーはO(4^K*K)程度。
 */
#include <iostream>
#include <vector>
#include <utility>
#include <cstdio>
#include <cmath>

using namespace std;

double dp[11][1024];

inline double win_prob(int p, int q) {
    return 1.0 / (1.0 + pow(10.0, (q - p) / 400.0));
}

// 敵は [start, end]
inline pair<int,int> range(int rnd, int person) {
    int mask = 1<<rnd;
    int rem = mask-1;
    int start = (person ^ mask) & ~rem;
    int end = (person ^ mask) | rem;
    return make_pair(start, end);
}

int main() {
    cin.tie(0);

    int K;
    cin >> K;
    const int N = 1<<K;
    vector<int> elo(N);
    for(int i = 0; i < N; ++i) {
        cin >> elo[i];
        dp[0][i] = 1.0;
    }

    for(int rnd = 1; rnd <= K; ++rnd) {
        for(int i = 0; i < N; ++i) {
            pair<int,int> r = range(rnd-1, i);
            for(int j = r.first; j <= r.second; ++j) {
                dp[rnd][i] += dp[rnd-1][j] * win_prob(elo[i], elo[j]);
            }
            dp[rnd][i] *= dp[rnd-1][i];
        }
    }
    for(int i = 0; i < N; ++i) {
        printf("%.7f\n", dp[K][i]);
    }
    return 0;
}
