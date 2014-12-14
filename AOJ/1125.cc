//Name: Get Many Persimmon Trees
//Level: 2
//Category: 動的計画法,DP,累積和
//Note:

/*
 * 二次元累積和で木の数を覚えておき、建物の左上座標を全通り試す。
 *
 * オーダーは O(WH)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    int W, H;
    cin >> W >> H;

    vector<vector<int>> field(H, vector<int>(W, 0));
    for(int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        field[y-1][x-1]++;
    }

    for(int r = 0; r < H; ++r) {
        for(int c = 0; c < W; ++c) {
            if(r > 0) field[r][c] += field[r-1][c];
            if(c > 0) field[r][c] += field[r][c-1];
            if(r > 0 && c > 0) field[r][c] -= field[r-1][c-1];
        }
    }

    int S, T;
    cin >> S >> T;
    int ans = 0;
    for(int r = 0; r <= H-T; ++r) {
        for(int c = 0; c <= W-S; ++c) {
            int sum = field[r+T-1][c+S-1];
            if(r > 0) sum -= field[r-1][c+S-1];
            if(c > 0) sum -= field[r+T-1][c-1];
            if(r > 0 && c > 0) sum += field[r-1][c-1];
            ans = max(ans, sum);
        }
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
