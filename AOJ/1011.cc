#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> dp(31, 1);

    dp[0] = dp[1] = 1;
    dp[2] = 2;
    int sum = 2;
    for(int i = 3; i <= 30; ++i) {
        if(i % 2 == 0) dp[i] = dp[i/2-1]*3*2+2;
        else dp[i] = dp[i/2]*4+1;
    }

    int N;
    while(cin >> N && !cin.eof()) {
        cout << dp[N] << endl;
    }
    return 0;
}
