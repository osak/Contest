//Name: Good Sequences
//Level: 3
//Category: 動的計画法,DP,数学,Math,素因数分解
//Note:

/**
 * 「ある素因数をもつ数が最後になるようなGood Sequenceの最大長」についてDP。
 * 先頭からなめていくと、ある数vを末尾に置くとき、
 *   dp[vの素因数] = max dp[vの素因数]+1
 * として更新すればよい。
 *
 * オーダーは O(N log V)。
 * ただし V は a_i の最大値。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int LIM = 100000;
int divisor_of[LIM+1];

void init() {
    divisor_of[1] = 1;
    for(int i = 2; i <= LIM; ++i) {
        if(divisor_of[i] == 0) {
            divisor_of[i] = i;
            for(long long j = (long long)i * i; j <= LIM; j += i) {
                if(divisor_of[j] == 0) divisor_of[j] = i;
            }
        }
    }
}

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<int> dp(100001, 0);
    dp[1] = 1;
    for(int i = 0; i < N; ++i) {
        int v;
        cin >> v;
        int best = 0;
        int tmp = v;
        while(tmp > 1) {
            best = max(best, dp[divisor_of[tmp]] + 1);
            tmp /= divisor_of[tmp];
        }
        tmp = v;
        while(tmp > 1) {
            dp[divisor_of[tmp]] = max(dp[divisor_of[tmp]], best);
            tmp /= divisor_of[tmp];
        }
    }
    cout << *max_element(dp.begin(), dp.end()) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    init();
    while(solve()) ;
    return 0;
}
