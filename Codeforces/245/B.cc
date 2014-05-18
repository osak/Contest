//Name: Working out
//Level: 2
//Category: 動的計画法,DP
//Note:

/**
 * 交差点では曲がれないので、その1歩手前に到着するパターンと、1歩後から出て行くパターンで考える。
 * 四隅から各点へ行く時の最高スコアを事前に計算しておき、交差点の候補と侵入方向をすべて試す。
 *
 * オーダーは O(RC)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;

void acc(vector<vector<LL>> &v) {
    const int R = v.size();
    const int C = v[0].size();
    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            const int u = i > 0 ? v[i-1][j] : 0;
            const int l = j > 0 ? v[i][j-1] : 0;
            v[i][j] = max(u, l) + v[i][j];
        }
    }
}

bool solve() {
    int R, C;
    if(!(cin >> R >> C)) return false;
    if(!R && !C) return false;

    vector<vector<LL>> m(R, vector<LL>(C));
    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            cin >> m[i][j];
        }
    }
    auto m1_from = m;
    acc(m1_from);

    auto m1_to = m;
    reverse(m1_to.begin(), m1_to.end());
    for(auto &v : m1_to) {
        reverse(v.begin(), v.end());
    }
    acc(m1_to);
    for(auto &v : m1_to) {
        reverse(v.begin(), v.end());
    }
    reverse(m1_to.begin(), m1_to.end());

    auto m2_from = m;
    reverse(m2_from.begin(), m2_from.end());
    acc(m2_from);
    reverse(m2_from.begin(), m2_from.end());

    auto m2_to = m;
    for(auto &v : m2_to) {
        reverse(v.begin(), v.end());
    }
    acc(m2_to);
    for(auto &v : m2_to) {
        reverse(v.begin(), v.end());
    }

    LL ans = 0;
    for(int r = 1; r < R-1; ++r) {
        for(int c = 1; c < C-1; ++c) {
            ans = max(ans, m1_from[r-1][c] + m1_to[r+1][c] + m2_from[r][c-1] + m2_to[r][c+1]);
            ans = max(ans, m1_from[r][c-1] + m1_to[r][c+1] + m2_from[r+1][c] + m2_to[r-1][c]);
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
