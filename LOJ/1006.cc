#include <iostream>

using namespace std;

int memo[6];
const int MOD = 10000007;

int main() {
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    for(int CASE = 1; CASE <= T; ++CASE) {
        for(int i = 0; i < 6; ++i) {
            cin >> memo[i];
            memo[i] %= MOD;
        }
        int N;
        cin >> N;

        int ans = 0;
        if(N < 6) {
            ans = memo[N] % MOD;
        }
        else {
            for(int n = 6; n <= N; ++n) {
                int next = 0;
                for(int i = 0; i < 6; ++i) {
                    next += memo[i];
                    if(i+1 < 6) memo[i] = memo[i+1];
                }
                memo[5] = next % MOD;
            }
            ans = memo[5];
        }

        cout << "Case " << CASE << ": " << ans << endl;
    }

    return 0;
}
