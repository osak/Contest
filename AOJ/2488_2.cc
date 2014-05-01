//Name: Tree Construction
//Level: 3
//Category: 木,Tree,動的計画法,DP
//Note:

/**
 * 右か上にしか辺を伸ばせないので、これは二分木になる。
 * 座標の制約から、上に伸ばした辺に対応させる頂点と、右に伸ばした辺に対応させる頂点は、
 * 中間のどこかを境として分割することができる。
 * したがって、これを再帰的に繰り返していけばよい。
 * それぞれの部分木の根は、部分木に含まれる頂点群の(最小のx, 最小のy)である。
 *
 * これはコストが単調(S⊂Tのとき、Sのコスト < Tのコスト)であり、かつMonge性
 * (w(l,r) + w(l',r') ≦ w(l,r') + w(l',r) が l ≦ l' ≦ r ≦ r' について成立する)
 * を満たしているため、Knuth-Yao Speedupが適用できる。
 * (この問題では等号で成立している？)
 *
 * オーダーはO(N^2)。
 */
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int dp[1024][1024];
int yao[1024][1024];
bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<pair<int,int>> nodes(N);
    for(int i = 0; i < N; ++i) {
        cin >> nodes[i].first >> nodes[i].second;
    }
    for(int i = 0; i <= N+1; ++i) {
        for(int j = 0; j <= N+1; ++j) {
            dp[i][j] = 2 * 10000 * 10000;
            yao[i][j] = 0;
        }
    }
    for(int i = 0; i <= N+1; ++i) {
        dp[i][i+1] = 0;
        yao[i][i+1] = i;
    }
    for(int r = 1; r <= N; ++r) {
        for(int l = r-1; l >= 0; --l) {
            const pair<int,int> root(nodes[l].first, nodes[r-1].second);
            for(int m = yao[l][r-1]; m <= yao[l+1][r]; ++m) {
                const int d = nodes[m-1].second - root.second + nodes[m].first - root.first;
                const int cost = dp[l][m] + dp[m][r] + d;
                if(cost <= dp[l][r]) {
                    dp[l][r] = cost;
                    yao[l][r] = m;
                }
            }
        }
    }
    cout << dp[0][N] << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
