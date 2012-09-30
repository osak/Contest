//Name: Kannondou
//Level: 1
//Category: 数列,トリボナッチ
//Note:

/*
 * トリボナッチ数列のN項目を求めればよい．
 */
#include <iostream>

using namespace std;

int dp[31];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    dp[0] = 1;
    for(int i = 1; i <= 30; ++i) {
        for(int j = 1; j <= 3; ++j) {
            if(i-j >= 0) dp[i] += dp[i-j];
        }
    }

    while(true) {
        int N;
        cin >> N;
        if(!N) break;
        cout << (dp[N]+3650-1)/3650 << endl;
    }
    return 0;
}
