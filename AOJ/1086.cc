//Name: Live Schedule
//Level: 3
//Category: 動的計画法,DP
//Note:

/**
 * ある区間でライブが開催できるかと、その区間における利益、負担は累積和を使うとO(1)で計算できる。
 * 状態としては、(現在の日付,連続公演を行った回数,負担合計)を使い、各状態ごとに最大の利益を管理する。
 * 状態数はO(CDW)、ライブを行う候補の区間数はO(C^2)であるから、全体のオーダーは O(C^3DW)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// sum of [l, r]
int get(const vector<int> &v, int l, int r) {
    if(l <= 0) return v[r];
    return v[r] - v[l-1];
}

bool solve() {
    int C, D, W, X;
    if(!(cin >> C >> D >> W >> X)) return false;
    if(!C && !D && !W && !X) return false;

    vector<vector<int>> es(D, vector<int>(C));
    vector<vector<int>> ps(D, vector<int>(C)); // prohibition
    vector<vector<int>> fs(D, vector<int>(C));
    for(int i = 0; i < C; ++i) {
        for(int j = 0; j < D; ++j) {
            cin >> es[j][i];
            ps[j][i] = es[j][i] == 0;
            if(i > 0) es[j][i] += es[j][i-1];
            if(i > 0) ps[j][i] += ps[j][i-1];
        }
    }
    for(int i = 0; i < C; ++i) {
        for(int j = 0; j < D; ++j) {
            cin >> fs[j][i];
            if(i > 0) fs[j][i] += fs[j][i-1];
        }
    }

    vector<vector<vector<int>>> dp(D, vector<vector<int>>(X+1, vector<int>(W+1, 0)));
    for(int d = 0; d < D; ++d) {
        for(int x = 0; x <= X; ++x) {
            for(int w = 0; w <= W; ++w) {
                if(d > 0) dp[d][x][w] = dp[d-1][x][w]; // ライブをしない場合
                for(int l = 0; l < C; ++l) {
                    for(int r = l; r < C; ++r) {
                        if(get(ps[d], l, r) != 0) break;
                        const int px = x - (l != r);
                        const int pw = w - get(fs[d], l, r);
                        if(px < 0 || pw < 0) continue;
                        int nv = get(es[d], l, r);
                        if(d > 0) nv += dp[d-1][px][pw];
                        dp[d][x][w] = max(dp[d][x][w], nv);
                    }
                }
            }
        }
    }
    int ans = -1;
    for(int x = 0; x <= X; ++x) {
        for(int w = 0; w <= W; ++w) {
            ans = max(ans, dp[D-1][x][w]);
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
