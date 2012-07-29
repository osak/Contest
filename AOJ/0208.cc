#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ULL;

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        /*
        vector<ULL> dp(11, 0);
        dp[0] = 0;
        dp[1] = 7;
        for(int i = 2; i <= 10; ++i) 
            dp[i] = 7 * (dp[i-1] + dp[i-2]);

        int arr[] = {0, 1, 2, 3, 5, 7, 8, 9};
        for(int i = 10; i >= 1; --i) {
            cout << arr[N / dp[i]];
            N %= dp[i];
        }
        cout << arr[N] << endl;
        */

        vector<int> digits;
        while(N) {
            digits.push_back(N % 8);
            N /= 8;
        }
        for(int i = digits.size()-1; i >= 0; --i) {
            cout << "01235789"[digits[i]];
        }
        cout << endl;
    }
    return 0;
}
