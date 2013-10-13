//Name: 数
//Level: 3
//Category: DP,動的計画法,Digit DP
//Note: Typical DP Contest E

/**
 * よくあるDigit DP。
 * 各桁を上から決めていき、過去の桁がすべて上限値と同じ数であれば、現在の桁も上限値によって制約される。
 * そうでなければ、0-9の任意の数を取ることができる。
 * 状態は[桁位置][現在の和][上限制約有無]。
 *
 * オーダーはO(LD)。
 * ただしLはNの桁数。
 * また、係数として上限制約による2、桁の数値を全て試すことによる10がかかる。
 */
#include <iostream>
#include <string>

using namespace std;

typedef long long LL;

const LL MOD = 1000000007LL;
LL memo[10001][101][2];
bool visited[10001][101][2];
int D;
string limit;

LL calc(int pos, int rem, bool limited) {
    if(pos == limit.size()) {
        if(rem == 0) return 1;
        return 0;
    }
    if(visited[pos][rem][limited]) {
        return memo[pos][rem][limited];
    }
    const int lim = limited ? limit[pos] - '0' : 9;
    LL res = 0;
    for(int digit = 0; digit <= lim; ++digit) {
        int nrem = rem - digit;
        if(nrem < 0) {
            nrem += D*(-nrem / D + 1);
        }
        res += calc(pos+1, nrem % D, limited && digit == lim);
        res %= MOD;
    }
    visited[pos][rem][limited] = true;
    return memo[pos][rem][limited] = res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> D >> limit;
    cout << calc(0, D, true)-1 << endl;
    return 0;
}
