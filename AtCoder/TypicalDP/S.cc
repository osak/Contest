//Name: マス目
//Level: 5
//Category: DP,動的計画法
//Note: Typical DP Contest S

/**
 * 1行ずつマス目を埋めていくとき、状態は
 * ・各マスが左上と繋がっているか (2^H通り)
 * ・各マスを相互に行き来できるか (2^(H(H-1)/2)通り)
 * の2つ。
 * これらの間の遷移表をがんばって作り、DPに持ち込む。
 * ただし実現不可能な状態も多いため、実現可能な状態のみを選ばないとTLEする。
 *
 * オーダーはO(W * 2^(3*H+H^2))。
 * ただし前述の通り、有効な状態数はかなり少なく、H=6のときに多くとも82944通りで抑えられる。
 */
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

typedef long long LL;

const LL MOD = 1000000007;

void add(LL &var, LL val) {
    var = (var + val) % MOD;
}

int map1[1<<6][1<<15];
pair<short,short> conn_map[90000][1<<6];
LL dp[2][1<<6][1<<15];
int main() {
    int H, W;
    cin >> H >> W;

    const int CONN_NUM = H*(H-1)/2;
    const int CONN_PAT = 1 << CONN_NUM;
    const int MASK_PAT = 1 << H;
    vector<pair<int,int>> valid_pairs;
    for(int lt_mask = 0; lt_mask < MASK_PAT; ++lt_mask) {
        for(int conn = 0; conn < CONN_PAT; ++conn) {
            const int idx = valid_pairs.size();
            vector<int> conn_mask(H, 0);
            {
                int pat = 1;
                for(int i = 0; i < H; ++i) {
                    conn_mask[i] |= (1<<i);
                    for(int j = 0; j < i; ++j) {
                        if(conn & pat) {
                            conn_mask[i] |= (1<<j);
                            conn_mask[j] |= (1<<i);
                        }
                        pat <<= 1;
                    }
                }
            }
            // Check consistency
            // if connected two cells has different connect-to-left-top-state, it is invalid
            for(int i = 0; i < H; ++i) {
                for(int j = 0; j < H; ++j) {
                    if(conn_mask[i] & (1<<j)) {
                        bool li = !!(lt_mask & (1<<i));
                        bool lj = !!(lt_mask & (1<<j));
                        if(li != lj) goto next;
                    }
                }
            }
            map1[lt_mask][conn] = idx;
            valid_pairs.push_back(make_pair(lt_mask, conn));
            for(int mask = 0; mask < MASK_PAT; ++mask) {
                // make new connection map
                vector<int> mat = conn_mask;
                for(int i = 0; i < H; ++i) {
                    if(~mask & (1<<i)) {
                        for(int j = 0; j < H; ++j) {
                            mat[j] &= ~(1<<i);
                        }
                        mat[i] = 0;
                    }
                }
                for(int i = 1; i < H; ++i) {
                    if((mask & (1<<i)) && (mask & (1<<(i-1)))) {
                        mat[i] |= mat[i-1];
                    }
                }
                for(int i = 0; i < H; ++i) {
                    for(int j = 0; j < H; ++j) {
                        if((mat[i] & (1<<j)) || (mat[j] & (1<<i))) {
                            mat[i] = mat[j] = mat[i] | mat[j];
                        }
                    }
                }
                int next_conn = 0;
                int next_lt = 0;
                int pat = 1;
                for(int i = 0; i < H; ++i) {
                    for(int j = 0; j < i; ++j) {
                        if(mat[i] & (1<<j)) {
                            next_conn |= pat;
                        }
                        pat <<= 1;
                    }
                }
                for(int i = 0; i < H; ++i) {
                    if((mask & (1<<i)) && (lt_mask & (1<<i))) {
                        next_lt |= mat[i];
                    }
                }
                conn_map[idx][mask] = make_pair(next_lt, next_conn);
            }
next:
            ;
        }
    }

    for(int i = 0; i < MASK_PAT; ++i) {
        if(i & 1) {
            const auto &p = conn_map[map1[1][0]][i];
            add(dp[0][p.first][p.second], 1);
            //cout << i << ' ' << p.first << ' ' << p.second << endl;
        }
    }
    for(int x = 1; x < W; ++x) {
        const int cur = x % 2;
        const int prev = 1-cur;
        for(const auto &p : valid_pairs) {
            dp[cur][p.first][p.second] = 0;
        }
        for(const auto &p : valid_pairs) {
            const int idx = map1[p.first][p.second];
            for(int mask = 0; mask < MASK_PAT; ++mask) {
                const auto &np = conn_map[idx][mask];
                //cout << p.first << ' ' << p.second << ' ' << mask << ' ' << np.first << ' ' << np.second << endl;
                //assert(find(valid_pairs.begin(), valid_pairs.end(), np) != valid_pairs.end());
                add(dp[cur][np.first][np.second], dp[prev][p.first][p.second]);
            }
        }
    }
    LL ans = 0;
    for(const auto &p : valid_pairs) {
        if(p.first & (1<<(H-1))) {
            add(ans, dp[1-W%2][p.first][p.second]);
        }
    }
    cout << ans << endl;
    return 0;
}
