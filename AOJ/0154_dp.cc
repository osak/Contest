//Name: Sum of Cards
//Level: 2
//Category: 動的計画法,DP
//Note:

/*
 * dp[i][j]をi種類目のカードまでを使ってjを作るパターン数とすると，
 *   dp[i][j] = Σ(0≦k≦b_i) dp[i-1][j - a_i*k]
 * となる．
 *
 * 以下のコードでは，iのインデックスを1-originにしてベースケースを簡単にし，また配るDPにして書きやすくしている．
 * オーダーは O(M*G*B)．ただしGは合計値の最大(1000)，Bはカード枚数の最大(10)．
 */
#include <iostream>
#include <vector>

using namespace std;

int dp[8][1001];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(true) {
        int M;
        cin >> M;
        if(!M) break;
        dp[0][0] = 1;
        for(int i = 1; i <= M; ++i) {
            int A, B;
            cin >> A >> B;
            for(int j = 0; j < 1001; ++j) dp[i][j] = 0;
            for(int j = 0; j < 1001; ++j) {
                for(int k = 0; k <= B; ++k) {
                    const int next = j + A*k;
                    if(next <= 1000) dp[i][next] += dp[i-1][j];
                }
            }
        }
        int N;
        cin >> N;
        while(N--) {
            int NG;
            cin >> NG;
            cout << dp[M][NG] << endl;
        }
    }
    return 0;
}
