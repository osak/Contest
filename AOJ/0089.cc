//Name: The Shortest Path on A Rhombic Path
//Level: 2
//Category: 動的計画法,DP
//Note:

/*
 * 上からたどっていって(row, col)にたどり着いたときの最大値をdp[row][col]とすると
 *   dp[row][col] = max(dp[row-1][left-top-of(row,col)], dp[row-1][right-top-of(row,col)]) + a[row][col]
 * ひし形の上半分と下半分でleft-top-ofとright-top-ofの計算式が変わることに注意．
 * また，以下のコードでは更新式を変形して配るDP形式にしている．
 *
 * オーダーはひし形の行数を N として O(N^2)．
 */
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int arr[100][100];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    string line;
    int pos = 0;
    while(cin >> line) {
        for(int i = 0; i < (int)line.size(); ++i) {
            if(line[i] == ',') line[i] = ' ';
        }
        istringstream is(line);
        for(int i = 0; !is.eof(); ++i) {
            is >> arr[pos][i];
        }
        ++pos;
    }
    const int N = pos;
    const int center = N / 2;
    vector<int> dp[2];
    dp[0].resize(100);
    dp[1].resize(100);
    dp[0][0] = arr[0][0];
    for(int i = 0; i < center; ++i) {
        fill(dp[1].begin(), dp[1].end(), 0);
        for(int j = 0; j <= i; ++j) {
            // left
            dp[1][j] = max(dp[1][j], dp[0][j] + arr[i+1][j]);
            // right
            dp[1][j+1] = max(dp[1][j+1], dp[0][j] + arr[i+1][j+1]);
        }
        dp[0].swap(dp[1]);
    }
    for(int i = center; i < N-1; ++i) {
        fill(dp[1].begin(), dp[1].end(), 0);
        for(int j = 0; j < N-i; ++j) {
            // left
            if(j > 0) dp[1][j-1] = max(dp[1][j-1], dp[0][j] + arr[i+1][j-1]);
            // right
            dp[1][j] = max(dp[1][j], dp[0][j] + arr[i+1][j]);
        }
        dp[0].swap(dp[1]);
    }
    cout << dp[0][0] << endl;
    return 0;
}
