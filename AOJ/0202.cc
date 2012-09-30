//Name: At Boss's Expense
//Level: 2
//Category: 素数
//Note:

/*
 * 料理の金額の組み合わせで作れる素数を求めればよい．
 * 作れる金額は単純にX要素をなめるDPで求められる．
 *
 * オーダーは素数列挙が O(n log n)，DPが(NX)．
 */
#include <iostream>
#include <cmath>

using namespace std;

const int LIM = 1000001;
const int SQRT = sqrt(LIM);
bool dp[LIM];
bool is_prime[LIM];

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    for(int i = 0; i < LIM; ++i) {
        is_prime[i] = true;
    }
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i <= SQRT; ++i) {
        if(is_prime[i]) {
            for(int j = i*i; j < LIM; j += i) {
                is_prime[j] = false;
            }
        }
    }
    while(true) {
        int N, X;
        cin >> N >> X;
        if(!N && !X) break;
        for(int i = 0; i <= X; ++i) {
            dp[i] = false;
        }
        dp[0] = true;
        int ans = -1;
        while(N--) {
            int A;
            cin >> A;
            for(int i = A; i <= X; ++i) {
                if(dp[i-A]) {
                    dp[i] = true;
                    if(is_prime[i]) ans = max(ans, i);
                }
            }
        }
        if(ans == -1) cout << "NA" << endl;
        else cout << ans << endl;
    }
    return 0;
}
