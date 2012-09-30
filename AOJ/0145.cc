//Name: Cards
//Level: 2
//Category: 動的計画法,DP,メモ化再帰
//Note:

/*
 * 区間[i,j]を一つの山にまとめるときの最小コストをdp[i][j]とすると，この山を作るために2つの山[i,k]と[k+1,j]を重ねているはずなので
 *   dp[i][j] = min(k) dp[i][k] + dp[k+1][j] + cost[i][k]*cost[k+1][j]
 * として計算できる．
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <climits>

using namespace std;

//dp[i][j] = [i,j]をすべてまとめるときの最小コスト
int dp[128][100];

int solve(const vector<pair<int,int> > &v, int left, int right) {
    int &res = dp[left][right];
    if(res < INT_MAX) return res;
    for(int split = left; split < right; ++split) {
        const int lcost = solve(v, left, split);
        const int rcost = solve(v, split+1, right);
        const int cost = v[left].first*v[split].second * v[split+1].first*v[right].second;
        res = min(res, lcost+rcost+cost);
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int N;
    cin >> N;
    vector<pair<int,int> > v(N);
    for(int i = 0; i < N; ++i) {
        cin >> v[i].first >> v[i].second;
    }
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if(i == j) dp[i][j] = 0;
            else dp[i][j] = INT_MAX;
        }
    }
    cout << solve(v, 0, N-1) << endl;
    return 0;
}
