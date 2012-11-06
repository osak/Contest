//Name: Grid
//Level: 2
//Category: 数学,動的計画法,DP
//Note:

/*
 * ループしているグリッドなので，右から回るか左から回るかで近い方を選ぶ(上下も同様)．
 * 選んだ後はCombinationでパターン数を求めればよい．
 * 右から行っても左から行っても同じ距離の場合はどっちを通っても良いのでパターン数が2倍になるが，
 * 距離0のときは例外となることに注意．
 *
 * オーダーはコンビネーションの計算で O(R+C)．
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 100000007;

int memo[1001][1001];
int comb(int n, int r) {
    if(r == 0) return 1;
    if(n == r) return 1;
    if(n < r) return 0;
    if(memo[n][r] != 0) return memo[n][r];
    return memo[n][r] = (comb(n-1, r) + comb(n-1, r-1)) % MOD;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int R, C;
    pair<int,int> start, goal;
    while(cin >> R >> C >> start.first >> start.second >> goal.first >> goal.second) {
        const int left = (start.second - goal.second+C) % C;
        const int right = (goal.second - start.second+C) % C;
        const int up = (start.first - goal.first+R) % R;
        const int down = (goal.first - start.first+R) % R;
        const int mc = min(left, right);
        const int mr = min(up, down);
        int pat = comb(mc+mr, mc);
        if(left != 0 && left == right) pat = (pat*2) % MOD;
        if(up != 0 && up == down) pat = (pat*2) % MOD;
        cout << pat << endl;
    }
    return 0;
}
