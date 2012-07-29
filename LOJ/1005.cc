#include <iostream>

using namespace std;

long long comb[31][31];

int main() {
    int T;
    cin >> T;

    for(int n = 0; n <= 30; ++n) {
        comb[n][0] = 1;
        for(int k = 1; k <= n; ++k) {
            comb[n][k] = comb[n-1][k-1] + comb[n-1][k];
        }
    }

    for(int CASE = 1; CASE <= T; ++CASE) {
        int N, K;
        cin >> N >> K;

        long long ans = 1;
        if(K > N) {
            ans = 0;
        }
        else {
            for(int i = 1; i <= K; ++i) ans *= i;
            ans *= comb[N][K];
            ans *= comb[N][K];
        }
        cout << "Case " << CASE << ": " << ans << endl;
    }

    return 0;
}
