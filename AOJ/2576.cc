//Name: Doctor Course Is Recommended
//Level: 2
//Category: 動的計画法,DP
//Note: RUPC 2014 Day3

/**
 * 選択肢がDかDDのもののみ利用可能。
 * Dをx個書いた時に得られる最大得点についてDPすればよい。
 *
 * オーダーは O(D(X+Y))。
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void process(vector<int> &dp) {
    int N;
    cin >> N;
    while(N--) {
        string s;
        int v;
        cin >> s >> v;
        if(s == "D" || s == "DD") {
            const int cost = s.size();
            for(int i = (int)dp.size() - 1; i >= cost; --i) {
                if(dp[i-cost] != -1) {
                    dp[i] = max(dp[i], dp[i-cost] + v);
                }
            }
        }
    }
}

bool solve() {
    int D;
    if(!(cin >> D)) return false;

    vector<int> dp(D+1, -1);
    dp[0] = 0;
    process(dp);
    process(dp);
    cout << *max_element(begin(dp), end(dp)) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
