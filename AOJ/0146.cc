//Name: Lupin The 4th
//Level: 3
//Category: 動的計画法,DP,メモ化再帰,ビットDP
//Note:

/*
 * 状態になるのは破った蔵の組み合わせと現在位置．
 * 持っている千両箱の重さは破った蔵の組から求められる．
 * これらの各状態について，最短でたどり着くときの時間を求め，最後に経路復元すればよい．
 * 状態[state][pos]における最短時間は直前にいた蔵として可能なものを全て列挙し，
 * それらにたどり着く最短時間に移動時間を加えたものの最小値である．
 *
 * オーダーは状態数が2^N*N，各状態から最大でN個の遷移を考えるので O(2^N * N^2)．
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double memo[1<<15][15];
int prev[1<<15][15];
double speed[1<<15];
int dist[15];
int weight[15];
int id[15];
int N;

double solve(int state, int pos) {
    double &res = memo[state][pos];
    if(res >= 0) return res;

    res = 1e30;
    const int prev_state = state & ~(1<<pos);
    for(int i = 0; i < N; ++i) {
        const int mask = 1<<i;
        if(prev_state & mask) {
            const double t = solve(prev_state, i) + abs(dist[pos]-dist[i]) / speed[prev_state];
            //cout << state << ' ' << pos << ' ' << i << ' ' << t << endl;
            if(t < res) {
                res = t;
                prev[state][pos] = i;
            }
        }
    }
    //cout << state << ' ' << pos << ' ' << res << endl;
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    for(int i = 0; i < N; ++i) {
        cin >> id[i] >> dist[i] >> weight[i];
    }

    // DP表の初期化
    const int TERMINAL = (1<<N)-1;
    for(int i = 0; i <= TERMINAL; ++i) {
        for(int j = 0; j < N; ++j) {
            memo[i][j] = (i == (1<<j)) ? 0 : -1;
            prev[i][j] = -1;
        }
    }

    // 蔵の組み合わせに対する速度の事前計算
    for(int i = 0; i <= TERMINAL; ++i) {
        int sum = 0;
        for(int j = 0; j < N; ++j) {
            if(i & (1<<j)) sum += weight[j];
        }
        speed[i] = 2000.0 / (70+sum*20);
        //cout << speed[i] << endl;
    }

    for(int i = 0; i < N; ++i) {
        solve(TERMINAL, i);
    }

    // 最短時間のとき，最後の蔵を求める．
    int cur = 0;
    for(int i = 1; i < N; ++i) {
        if(memo[TERMINAL][i] < memo[TERMINAL][cur]) {
            cur = i;
        }
    }

    // 経路復元
    int state = TERMINAL;
    vector<int> ans;
    while(cur != -1) {
        ans.push_back(id[cur]);
        int next = prev[state][cur];
        state &= ~(1<<cur);
        cur = next;
    }

    reverse(ans.begin(), ans.end());
    for(int i = 0; i < N; ++i) {
        if(i > 0) cout << ' ';
        cout << ans[i];
    }
    cout << endl;
    return 0;
}
