#include <iostream>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;
int dp[2][5001];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    int *cur = dp[0], *prev = dp[1];
    for(int i = 0; i < N; ++i) {
        int h;
        cin >> h;
        fill_n(cur, 5001, 0);
        for(int j = 0; j <= N/2; ++j) {
            if(h != -1 && j != h) continue;
            if(i == 0) {
                if(j == 0) cur[j] = 1;
            } else {
                cur[j] = prev[j];
                if(j > 0) {
                    cur[j] += prev[j-1];
                    cur[j] %= MOD;
                }
                if(j < N/2) {
                    cur[j] += prev[j+1];
                    cur[j] %= MOD;
                }
            }
        }
        swap(cur, prev);
    }
    cout << prev[0] << endl;
    return 0;
}
