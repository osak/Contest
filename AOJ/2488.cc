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
 * オーダーはO(N^3)。
 */
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int memo[1024][1024];
int calc(int l, int r, const vector<pair<int,int>> &nodes) {
    if(memo[l][r] >= 0) return memo[l][r];
    if(l+1 == r) return 0;
    pair<int,int> root(min(nodes[l].first, nodes[r-1].first), min(nodes[l].second, nodes[r-1].second));
    memo[l][r] = 10000 * 10000 * 2;
    for(int m = l+1; m < r; ++m) {
        const int d = nodes[m-1].second - root.second + nodes[m].first - root.first;
        memo[l][r] = min(memo[l][r], calc(l, m, nodes) + calc(m, r, nodes) + d);
    }
    return memo[l][r];
}

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<pair<int,int>> nodes(N);
    for(int i = 0; i < N; ++i) {
        cin >> nodes[i].first >> nodes[i].second;
    }
    for(int i = 0; i <= N; ++i) {
        for(int j = 0; j <= N; ++j) {
            memo[i][j] = -1;
        }
    }
    cout << calc(0, N, nodes) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
