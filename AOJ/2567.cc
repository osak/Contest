//Name: SIRO Challenge
//Level: 3
//Category: グラフ,Graph,縮約,巡回セールスマン問題,TSP,練習問題
//Note:

/**
 * 問題となるのはいくつの店を回ったかであるから、あるパターンで店が訪問済みになる最短時間を覚えておけば良い。
 * これは巡回セールスマン問題のようにすればできる。
 * ただし、与えられたグラフに対してそのまま訪問済みの店集合を持たせるように拡張すると、頂点数が多くなりすぎるため、先に縮約しておく。
 * 縮約は、全点対最短距離を求めておき、スタートと店だけからなるグラフに再構成すればよい（Dijkstra法などを使えばもっと速くなる）。
 *
 * グラフが連結とは限らないことに注意。
 *
 * オーダーは O(N^3 + L^2 2^L)。
 */

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <unordered_map>

using namespace std;

bool solve() {
    int N, M, L, S, T;
    if(!(cin >> N >> M >> L >> S >> T)) return false;
    if(!N && !M && !L && !S && !T) return false;
    --S;

    vector<vector<int>> org_g(N, vector<int>(N, -1));
    for(int i = 0; i < M; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        org_g[a][b] = org_g[b][a] = c;
    }
    for(int i = 0; i < N; ++i) {
        org_g[i][i] = 0;
    }
    for(int k = 0; k < N; ++k) {
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                if(org_g[i][k] == -1 || org_g[k][j] == -1) continue;
                const int nl = org_g[i][k] + org_g[k][j];
                if(org_g[i][j] == -1 || org_g[i][j] > nl) {
                    org_g[i][j] = nl;
                }
            }
        }
    }

    // グラフを再構築する。
    unordered_map<int,int> dict;
    dict[0] = S;
    vector<vector<int>> graph(L+1, vector<int>(L+1, -1));
    vector<int> es(L+1, 0);
    for(int i = 1; i <= L; ++i) {
        int j;
        cin >> j >> es[i];
        --j;
        for(const auto &p : dict) {
            graph[p.first][i] = graph[i][p.first] = org_g[p.second][j];
        }
        dict[i] = j;
    }
    for(int i = 0; i <= L; ++i) {
        graph[i][i] = 0;
    }

    // TSP
    vector<vector<int>> dp(1<<(L+1), vector<int>(L+1, -1));
    dp[0][0] = 0;
    for(int pat = 0; pat < (1<<(L+1)); ++pat) {
        for(int i = 0; i <= L; ++i) {
            if(dp[pat][i] == -1) continue;
            for(int j = 0; j <= L; ++j) {
                if(graph[i][j] == -1) continue;
                const int nt = dp[pat][i] + graph[i][j] + es[j];
                const int np = pat | (1<<j);
                if(nt <= T && (dp[np][j] == -1 || dp[np][j] > nt)) {
                    dp[np][j] = nt;
                }
            }
        }
    }

    int ans = 0;
    for(int pat = 0; pat < (1<<(L+1)); ++pat) {
        if(dp[pat][0] != -1) {
            ans = max(ans, __builtin_popcount(pat & ~1));
        }
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
