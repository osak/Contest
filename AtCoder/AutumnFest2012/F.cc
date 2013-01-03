#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// split point
vector<vector<vector<int> > > prev(2, vector<vector<int> >(50, vector<int>(50)));
vector<vector<vector<double> > > dp(2, vector<vector<double> >(50, vector<double>(50, 0.0/0.0)));

// [left, right]
// 0 for min, 1 for max
double calc(int left, int right, int idx, const vector<double> &nums) {
    if(!isnan(dp[idx][left][right])) return dp[idx][left][right];
    if(left == right) {
        return dp[idx][left][right] = nums[left];
    }
    dp[0][left][right] = 1.0/0.0;
    dp[1][left][right] = -1.0/0.0;
    // split is in right
    for(int split = left+1; split <= right; ++split) {
        double val = calc(left, split-1, 1, nums) / calc(split, right, 0, nums);
        if(val < dp[0][left][right]) {
            dp[0][left][right] = val;
            prev[0][left][right] = split;
        }
        if(val > dp[1][left][right]) {
            dp[1][left][right] = val;
            prev[1][left][right] = split;
        }
    }
    return dp[idx][left][right];
}

int make_ans(int left, int right, int idx, int len, vector<int> &ans) {
    if(left == right) return len;
    const int split = prev[idx][left][right];
    ans[split-1] = len;
    const int nlen = make_ans(left, split-1, 1, len-1, ans);
    return make_ans(split, right, 0, nlen, ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int N;
    cin >> N;
    vector<double> nums(N);
    for(int i = 0; i < N; ++i) {
        cin >> nums[i];
    }
    //cout << calc(0, N-1, 1, nums) << endl;
    calc(0, N-1, 1, nums);
    vector<int> ans(N-1);
    int len = N-1;
    make_ans(0, N-1, 1, len, ans);
    for(int i = 0; i < N-1; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}
