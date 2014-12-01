//Name: Anipero 2012
//Level: 2
//Category: 動的計画法,DP
//Note:

/*
 * [i曲目][残り本数][レベル2を振る本数] = 累計満足度でDP。
 * 更新は、レベル1をl本振るとして、dp[i][j][k] = max(∀l,k'. dp[i-1][j+max(l-k',0)+k][k'] + f(i,l,k))
 * （レベル1を増やしたいとき、過去に遡って折っていたことにする；初日はレベル1を振れないことに注意）。
 * サイリウムを折っても、必ずしも振る必要はないことに注意。
 *
 * オーダーは O(NML^3)。
 * ただし、Lは同時に使えるサイリウムの最大本数で、L=8。
 */
#include <iostream>
#include <array>

using namespace std;

template <typename T>
struct Maybe {
    T val;
    bool valid;

    Maybe() : valid(false) {}
    Maybe(T &t) : val(t), valid(true) {}

    T& operator =(const T &rv) {
        val = rv;
        valid = true;
        return val;
    }
};

bool solve() {
    int N, M;
    if(!(cin >> N >> M)) return false;

    array<array<array<Maybe<int>,9>,51>,51> dp;
    dp[0][M][0] = 0;
    for(int i = 1; i <= N; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        for(int j = 0; j <= M; ++j) {
            for(int k = 0; k <= 8; ++k) {
                for(int l = 0; l <= 8-k; ++l) {
                    if(i == 1 && l > 0) break;
                    const int add = (k+l == 0) ? c : l*b + k*a;
                    for(int pk = 0; pk <= 8; ++pk) {
                        const int pj = j + max(0, l-pk) + k;
                        if(pj < 0 || pj > M) continue;
                        if(!dp[i-1][pj][pk].valid) continue;
                        const int ns = dp[i-1][pj][pk].val + add;
                        if(!dp[i][j][k].valid || dp[i][j][k].val < ns) dp[i][j][k] = ns;
                    }
                }
            }
        }
    }
    Maybe<int> ans;
    for(int j = 0; j <= M; ++j) {
        for(int k = 0; k <= 8; ++k) {
            if(dp[N][j][k].valid) {
                const int v = dp[N][j][k].val;
                if(!ans.valid || ans.val < v) ans = v;
            }
        }
    }
    cout << ans.val << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
