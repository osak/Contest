//Name: Curling 2.0
//Level: 3
//Category: 探索
//Note:

/**
 * 障害物が壊れるのが面倒だが、10回までしか石を動かせないので、状態数は4^10=2^20≒100万程度。
 * 1回の移動では1ラインだけ見ればよいので、普通にシミュレーションすれば2000万ループ程度で解ける。
 *
 * オーダーはO((W+H)4^N)。
 * ただしNは石を動かせる回数で、N=10。
 */

#include <iostream>
#include <vector>

using namespace std;

int W, H;
int ans;
const int DR[] = {0, -1, 0, 1};
const int DC[] = {1, 0, -1, 0};
void dfs(vector<vector<int>> &field, const pair<int,int> &p, int turn) {
    if(turn >= ans) return;
    if(turn >= 11) return;
    for(int d = 0; d < 4; ++d) {
        auto cur = p;
        bool first = true;
        while(true) {
            cur.first += DR[d];
            cur.second += DC[d];
            if(cur.first < 0 || cur.first >= H || cur.second < 0 || cur.second >= W) {
                break;
            }
            if(field[cur.first][cur.second] == 3) {
                ans = min(ans, turn);
                break;
            }
            if(field[cur.first][cur.second] == 1) {
                if(!first) {
                    field[cur.first][cur.second] = 0;
                    dfs(field, make_pair(cur.first-DR[d], cur.second-DC[d]), turn+1);
                    field[cur.first][cur.second] = 1;
                }
                break;
            }
            first = false;
        }
    }
}

bool solve() {
    if(!(cin >> W >> H)) return false;
    if(!W && !H) return false;

    vector<vector<int>> field(H, vector<int>(W, 0));
    pair<int,int> start;
    for(int r = 0; r < H; ++r) {
        for(int c = 0; c < W; ++c) {
            cin >> field[r][c];
            if(field[r][c] == 2) {
                start = make_pair(r, c);
            }
        }
    }

    ans = 100;
    dfs(field, start, 1);
    if(ans == 100) ans = -1;
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
