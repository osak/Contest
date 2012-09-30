//Name: Discounts of Buckwheat 
//Level: 1
//Category: 動的計画法,DP
//Note: 問題文がよくないが容量ぴったり買えばよい

/*
 * そば粉の元の値段と，割引き後の値段それぞれを荷物としてナップザック問題を解けばよい．
 * 容量が100の倍数なので100で割って量子化できる．
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

struct Tag {
    int amount;
    int cost;
    Tag(int a, int c) : amount(a), cost(c) {}
};
Tag BASE[] = {
    Tag(2, 380), Tag(3, 550), Tag(5, 850),
    Tag(2*5, 380*5*80/100), Tag(3*4, 550*4*85/100), Tag(5*3, 850*3*88/100)
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int N;
        cin >> N;
        if(!N) break;
        vector<int> dp(N/100 + 1, INT_MAX/2);
        dp[0] = 0;
        for(int i = 0; i <= N/100; ++i) {
            for(int j = 0; j < 6; ++j) {
                int prev = i - BASE[j].amount;
                if(prev >= 0) {
                    dp[i] = min(dp[i], dp[prev] + BASE[j].cost);
                }
            }
        }
        cout << dp[N/100] << endl;
    }
    return 0;
}

