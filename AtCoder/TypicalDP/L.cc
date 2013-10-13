//Name: 猫
//Level: 4
//Category: DP,動的計画法
//Note: Typical DP Contest L

/**
 * 猫iが巻き込む猫のうち、左端のものをleft_iとすると
 *   left_0 ≦ left_1 ≦ …… ≦ left_{N-1}
 * が成立する。
 * また、座標は実数でとれるから、上記の条件を満たしていれば、それを実現するような配置が必ず存在する。
 * したがって、dp[i][left] = (猫iがleftまで巻き込む時、猫iまでの幸福度の総和) とすると、
 * 猫iを配置したことによって増える幸福度は
 *   S_left = ∑f_{i, left≦j≦i} 
 * 更新式は
 *   dp[i][left] = dp[i-1][left'] + S_left
 *   ただし left'≦left
 * となる。
 *
 * オーダーはO(N^3)。
 */
#include <iostream>
#include <vector>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    vector<vector<int> > f(N, vector<int>(N, 0));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> f[i][j];
        }
    }

    // dp[i][j] = 猫i周辺の左端が猫j
    vector<vector<int> > dp(N, vector<int>(N, -1000*N*N));
    dp[0][0] = 0;
    for(int i = 1; i < N; ++i) {
        int sum = 0;
        for(int left = i; left >= 0; --left) {
            sum += f[i][left];
            for(int prev = left; prev >= 0; --prev) {
                dp[i][left] = max(dp[i][left], dp[i-1][prev] + sum);
                //cout << i << ' ' << left << ' ' << prev << ' ' << dp[i][left] << endl;
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < N; ++i) {
        ans = max(ans, dp[N-1][i]);
    }
    cout << ans*2 << endl;
    return 0;
}
