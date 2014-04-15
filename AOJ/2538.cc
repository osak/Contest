//Name: Stack Maze
//Level: 3
//Category: 動的計画法,DP
//Note:

/**
 * スタックなので、pushする場所とpopする場所を決めれば、その間でpushとpopの組み合わせを任意の回数入れることができる。
 * したがって、宝石を見つけたら入れる穴を決め、宝石-穴の矩形と穴-目的地の矩形のそれぞれで、再帰的に計算を行うことで
 * 構成できる組の個数が求められる。
 * （穴の個数は260個以下なので、分割回数は高々この回数である）
 *
 * 以上のDPは、ある矩形内を左上から右下へたどるときに実現できるpushとpopの組の最大個数として定式化できるので、
 * 状態数は2500^2個となる。
 * これをメモ化再帰で実装すればよいが、引数をintにするとスタックがあふれてしまうため、引数をbyteにする必要がある。
 *
 * オーダーはO((HW)^2 T)。
 * ただし、Tはある宝石に対応する穴の個数の最大値。
 */
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cctype>

using namespace std;

const int INF = 5000;
typedef unsigned char byte;

vector<string> field;
unordered_map<char, vector<pair<int,int>>> holes_of;
int dp[55][55][55][55];
bool visited[55][55][55][55];

int calc(byte t, byte l, byte b, byte r) {
    if(visited[t][l][b][r]) return dp[t][l][b][r];
    if(t > b || l > r) return -INF;
    if(field[t][l] == '#') return -INF;
    visited[t][l][b][r] = true;
    int &res = dp[t][l][b][r];
    if(t == b && l == r) {
        res = 0;
    } else {
        res = max(res, calc(t+1, l, b, r));
        res = max(res, calc(t, l+1, b, r));
        if(islower(field[t][l])) {
            // Pick and place
            for(const auto &to : holes_of[field[t][l]]) {
                //cout << field[t][l] << ' ' << to.first << ' ' << to.second << endl;
                if(to.first == b && to.second == r) continue;
                if(to.first < t || to.second < l) continue;
                res = max(res, calc(t+1, l, to.first, to.second) + 1 + calc(to.first, to.second, b, r));
                res = max(res, calc(t, l+1, to.first, to.second) + 1 + calc(to.first, to.second, b, r));
            }
        }
    }
    if(res < 0) res = -INF;
    return res;
}

bool solve() {
    int H, W;
    if(!(cin >> H >> W)) return false;
    if(!H && !W) return false;

    field.clear();
    field.resize(H);
    holes_of.clear();
    for(int i = 0; i < H; ++i) {
        cin >> field[i];
        for(int j = 0; j < W; ++j) {
            if(isupper(field[i][j])) {
                const char c = tolower(field[i][j]);
                holes_of[c].push_back(make_pair(i, j));
            }
        }
    }
    field.push_back(string(W, '#'));
    field.back()[W-1] = '.';
    fill_n((int*)dp, sizeof(dp)/sizeof(int), -INF);
    fill_n((bool*)visited, sizeof(visited)/sizeof(bool), false);

    int res = calc(0, 0, H, W-1);
    if(res < 0) res = -1;
    cout << res << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
