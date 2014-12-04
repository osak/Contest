//Name: Heian-Kyo Walking
//Level: 2
//Category: 動的計画法,DP
//Note:

/*
 * 通れないパターンを覚えておき、グリッドグラフの最短経路数え上げをする。
 *
 * オーダーは O(XY log P)。
 */
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int,int> Pt;

void solve() {
    int X, Y;
    cin >> X >> Y;
    int P;
    cin >> P;
    set<pair<Pt,Pt>> prohibited;
    for(int i = 0; i < P; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        prohibited.insert(make_pair(Pt(x1, y1), Pt(x2, y2)));
        prohibited.insert(make_pair(Pt(x2, y2), Pt(x1, y1)));
    }

    vector<vector<int>> dp(X+1, vector<int>(Y+1, 0));
    dp[0][0] = 1;
    for(int x = 0; x <= X; ++x) {
        for(int y = 0; y <= Y; ++y) {
            if(x > 0 && !prohibited.count(make_pair(Pt(x-1,y), Pt(x,y)))) dp[x][y] += dp[x-1][y];
            if(y > 0 && !prohibited.count(make_pair(Pt(x,y-1), Pt(x,y)))) dp[x][y] += dp[x][y-1];
        }
    }
    if(dp[X][Y] == 0) {
        cout << "Miserable Hokusai!" << endl;
    } else {
        cout << dp[X][Y] << endl;
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    while(N--) solve();
    return 0;
}
