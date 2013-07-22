//Name: Hot days
//Level: 3
//Category: 動的計画法,DP
//Note:

/*
 * [N日目][着る服] = 最大スコア のDP表を埋めていく。
 * 更新式は、max(dp[N-1日目][N-1日目に着た服] + 派手さの差分スコア)
 *
 * オーダーは O(DN^2)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Cloth {
    int low, high;
    int cost;

    bool suitable(int temp) const {
        return low <= temp && temp <= high;
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int D, N;
    cin >> D >> N;
    vector<int> temps(D);
    vector<Cloth> clothes(N);
    for(int i = 0; i < D; ++i) {
        cin >> temps[i];
    }
    for(int i = 0; i < N; ++i) {
        Cloth &cloth = clothes[i];
        cin >> cloth.low >> cloth.high >> cloth.cost;
    }

    vector<int> dp[2];
    dp[0].resize(N, 0);
    dp[1].resize(N, 0);
    for(int i = 1; i < D; ++i) {
        const int temp = temps[i];
        fill(dp[1].begin(), dp[1].end(), 0);
        for(int j = 0; j < N; ++j) {
            if(!clothes[j].suitable(temp)) continue;
            for(int prev = 0; prev < N; ++prev) {
                if(clothes[prev].suitable(temps[i-1])) {
                    dp[1][j] = max(dp[1][j], dp[0][prev] + abs(clothes[j].cost - clothes[prev].cost));
                }
            }
        }
        dp[0].swap(dp[1]);
    }

    cout << *max_element(dp[0].begin(), dp[0].end()) << endl;
    return 0;
}
