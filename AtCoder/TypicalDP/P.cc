//Name: うなぎ
//Level: 4
//Category: 木,Tree,動的計画法,DP
//Note:

/**
 * 適当な頂点を根としたrooted treeの上で考えてよい。
 *
 * 各頂点の状態は
 * ・パスに含まれない
 * ・パスの端点である
 * ・パスの中点である
 * のいずれか。
 * 0<=k<=Kについて、子がk個のパスを持てるパターン数が分かっていれば、自分自身のパターン数も
 * 場合分けによって計算が可能である。
 * 各頂点では、「i番目の子までを使ったときに実現できるパターン数」をナップサック問題のようにしてDPすればよい。
 *
 * オーダーはO(NK^2)。
 */
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

typedef long long LL;
const LL MOD = 1000000007;

vector<vector<int>> T;
void normalize(int pos, int root) {
    for(auto it = T[pos].begin(); it != T[pos].end(); ) {
        if(*it == root) {
            it = T[pos].erase(it);
        } else {
            normalize(*it, pos);
            ++it;
        }
    }
}

//dp[node][state][count]
//state = 0: alone
//        1: end of path
//        2: midpoint
LL dp[1000][3][51];
int N, K;

void add(LL &var, LL val) {
    var = (var + val%MOD) % MOD;
}

void assign(LL &var, LL val) {
    var = val % MOD;
}

void calc(int pos) {
    dp[pos][0][0] = 1;
    for(int child : T[pos]) {
        calc(child);
        static LL cur[3][51];
        for(int s = 0; s < 3; ++s) {
            for(int k = 0; k <= K; ++k) {
                cur[s][k] = dp[pos][s][k];
                dp[pos][s][k] = 0;
            }
        }
        for(int k = K; k >= 0; --k) {
            for(int prev = 0; prev <= k; ++prev) {
                // Keep alone
                {
                    LL fact = 0;
                    add(fact, dp[child][0][k-prev]);
                    add(fact, dp[child][1][k-prev]);
                    add(fact, dp[child][2][k-prev]);
                    add(dp[pos][0][k], cur[0][prev] * fact);
                }

                // Make this node end point
                {
                    LL fact = 0;
                    if(k-prev-1 >= 0) add(fact, dp[child][0][k-prev-1]);
                    add(fact, dp[child][1][k-prev]);
                    add(dp[pos][1][k], cur[0][prev] * fact);
                    fact = 0;
                    add(fact, dp[child][0][k-prev]);
                    add(fact, dp[child][1][k-prev]);
                    add(fact, dp[child][2][k-prev]);
                    add(dp[pos][1][k], cur[1][prev] * fact);
                }

                // Make this node mid-point
                {
                    LL fact = 0;
                    add(fact, dp[child][0][k-prev]);
                    if(k-prev+1 < N) add(fact, dp[child][1][k-prev+1]);
                    add(dp[pos][2][k], cur[1][prev] * fact);
                    fact = 0;
                    add(fact, dp[child][0][k-prev]);
                    add(fact, dp[child][1][k-prev]);
                    add(fact, dp[child][2][k-prev]);
                    add(dp[pos][2][k], cur[2][prev] * fact);
                }
            }
        }
    }
    /*
    cout << "pos " << pos << endl;
    for(int i = 0; i < 3; ++i) {
        cout << i << ": ";
        for(int k = 0; k <= K; ++k) {
            cout << dp[pos][i][k] << ' ';
        }
        cout << endl;
    }
    */
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> N >> K;
    T.resize(N);
    for(int i = 0; i < N-1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        T[a].push_back(b);
        T[b].push_back(a);
    }
    normalize(0, -1);
    calc(0);
    cout << (dp[0][0][K] + dp[0][1][K] + dp[0][2][K]) % MOD << endl;
    return 0;
}
