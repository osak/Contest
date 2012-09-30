//Name: Grid
//Level: 1
//Category: 動的計画法,DP
//Note:

/*
 * 各マスについて，縦，横，右下がり，左下がりのそれぞれの方向にどれだけ連続しているかをメモりながら数える．
 * 全部愚直に探索してもたぶん通る．
 * オーダーは全てのマスをなめるので O(N^2)．
 */
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Tag {
    int ver, hor, lr, rl;
    Tag() : ver(0), hor(0), lr(0), rl(0) {}
    Tag(int v, int h, int l, int r) : ver(v), hor(h), lr(l), rl(r) {}
};

Tag dp[2][255];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        for(int i = 0; i < N; ++i) {
            dp[0][i] = dp[1][i] = Tag(0, 0, 0, 0);
        }
        int ans = 0;
        for(int i = 0; i < N; ++i) {
            const int cur = i & 1;
            const int prev = cur ^ 1;
            string str;
            cin >> str;
            for(int c = 0; c < N; ++c) {
                dp[cur][c] = Tag(0, 0, 0, 0);
                if(str[c] == '1') {
                    if(i > 0) dp[cur][c].ver = dp[prev][c].ver;
                    if(c > 0) dp[cur][c].hor = dp[cur][c-1].hor;
                    if(i > 0 && c > 0) dp[cur][c].lr = dp[prev][c-1].lr;
                    if(i > 0 && c+1 < N) dp[cur][c].rl = dp[prev][c+1].rl;
                    ans = max(ans, ++dp[cur][c].ver);
                    ans = max(ans, ++dp[cur][c].hor);
                    ans = max(ans, ++dp[cur][c].lr);
                    ans = max(ans, ++dp[cur][c].rl);
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
