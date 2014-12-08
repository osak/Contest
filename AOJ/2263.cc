//Name: The First Acceptance
//Level: 3
//Category: 動的計画法,DP
//Note:

/**
 * B_iの大きい問題を先に解いてから小さい問題を解いても合計時間は変わらないため、B_iの小さい問題から順に解いていけばよい。
 *   dp[i][j] = i問目まででj問のFAを取った時にかかる最短時間
 * とすると、更新式は
 *   dp[i][j] = min(dp[i-1][j], dp[i-1][j-1] + A_i)
 * ただし、minの第2項はB_iを超えてはいけない。
 *
 * オーダーは O(N^2)。
 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename T>
struct Maybe {/*{{{*/
    T val;
    bool valid;

    Maybe() : valid(false) {}
    Maybe(T &t) : val(t), valid(true) {}

    T& operator =(const T &rv) {
        val = rv;
        valid = true;
        return val;
    }
};/*}}}*/

struct Problem {
    int a, b;

    bool operator <(const Problem &p) const {
        return b < p.b;
    }
};

bool solve() {
    int N;
    if(!(cin >> N)) return false;

    vector<Problem> ps(N);
    for(int i = 0; i < N; ++i) {
        cin >> ps[i].a >> ps[i].b;
    }
    sort(begin(ps), end(ps));

    vector<vector<Maybe<long long>>> dp(N, vector<Maybe<long long>>(N+1));
    dp[0][0] = 0LL;
    if(ps[0].b >= ps[0].a) {
        dp[0][1] = ps[0].a;
    }
    for(int i = 1; i < N; ++i) {
        for(int j = 0; j <= N; ++j) {
            dp[i][j] = dp[i-1][j];
            if(j > 0 && dp[i-1][j-1].valid) {
                const long long t = dp[i-1][j-1].val + ps[i].a;
                if(t <= ps[i].b && (!dp[i][j].valid || dp[i][j].val > t)) {
                    dp[i][j] = t;
                }
            }
        }
    }
    int ans = 0;
    for(int i = 0; i <= N; ++i) {
        if(dp[N-1][i].valid) ans = i;
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
