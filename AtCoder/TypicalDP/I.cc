//Name: イウィ
//Level: 3
//Category: 文字列,動的計画法,DP
//Note: Typical DP Contest I

/*
 * 区間[l, r)が完全に消せるかを考える。
 * この区間が完全に消せるとき、その構造は
 *   iwi(消せるパターン)
 *   iw(消せるパターン)i
 *   i(消せるパターン)wi
 *   (消せるパターン)iwi
 *   (消せるパターン)(消せるパターン)
 * のいずれかである。
 * これはDPやメモ化再帰によって計算できる。
 *
 * 消せる回数は、dp[r] = (str[0...r]についてiwiを消せる最大回数)とすると
 *   dp[r] = max(dp[l_i] + (r_i - l_i + 1) / 3)
 *   ただし、区間[l_i, r)は完全に消去可能
 * として計算できる。
 *
 * オーダーはO(N^3)。
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

enum State {
    UNDECIDED,
    CAN,
    CANNOT
};

State dp[301][301];
string str;

int calc(int l, int r) {
    if(dp[l][r] != UNDECIDED) return dp[l][r];
    if(l == r) return dp[l][r] = CAN;
    if(r-l < 3) return dp[l][r] = CANNOT;
    if(str[l] == 'i' && str[r-2] == 'w' && str[r-1] == 'i' && calc(l+1, r-2) == CAN) {
        return dp[l][r] = CAN;
    }
    if(str[l] == 'i' && str[l+1] == 'w' && str[r-1] == 'i' && calc(l+2, r-1) == CAN) {
        return dp[l][r] = CAN;
    }
    if(str[l] == 'i' && str[l+1] == 'w' & str[l+2] == 'i' && calc(l+3, r) == CAN) {
        return dp[l][r] = CAN;
    }
    if(str[r-3] == 'i' && str[r-2] == 'w' && str[r-1] == 'i' && calc(l, r-3) == CAN) {
        return dp[l][r] = CAN;
    }
    for(int m = l+1; m < r; ++m) {
        if(calc(l, m) == CAN && calc(m, r) == CAN) {
            return dp[l][r] = CAN;
        }
    }
    return dp[l][r] = CANNOT;
}

int main() {
    cin >> str;

    fill_n((State*)dp, sizeof(dp)/sizeof(State), UNDECIDED);
    const int N = str.size();
    vector<int> segdp(N+1, 0);
    for(int r = 1; r <= N; ++r) {
        for(int len = r; len >= 3; --len) {
            if(len % 3 != 0) continue;
            const int l = r - len;
            if(calc(l, r) == CAN) {
                for(int segl = -1; segl < l; ++segl) {
                    const int prev = (segl == -1) ? 0 : segdp[segl];
                    segdp[r] = max(segdp[r], prev + len / 3);
                }
            }
        }
    }
    cout << *max_element(segdp.begin(), segdp.end()) << endl;
    return 0;
}
