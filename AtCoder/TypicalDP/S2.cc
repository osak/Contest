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
 * ただし前述の通り、有効な状態数はかなり少なく、実測で176通り程度であった。
 */
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <unordered_map>

using namespace std;

typedef long long LL;

const LL MOD = 1000000007;

void add(LL &var, LL val) {
    var = (var + val) % MOD;
}

int H, W;

//int map1[1<<6][1<<15];
//pair<short,short> conn_map[90000][1<<6];
unordered_map<int,pair<short,short>> memo;
pair<short,short> calc_next(int lt_mask, int conn, int mask) {
    const int h = (((lt_mask << 15) + conn) << 6) + mask;
    if(memo.count(h)) return memo[h];

    vector<int> mat(H, 0);
    {
        int pat = 1;
        for(int i = 0; i < H; ++i) {
            mat[i] |= (1<<i);
            for(int j = 0; j < i; ++j) {
                if(conn & pat) {
                    mat[i] |= (1<<j);
                    mat[j] |= (1<<i);
                }
                pat <<= 1;
            }
        }
    }
    // make new connection map
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
    return memo[h] = make_pair(next_lt, next_conn);
}

unordered_map<int,LL> calc_memo[100];
LL calc(int x, short lt_mask, short conn) {
    if(x == W) {
        if(lt_mask & (1<<(H-1))) return 1;
        return 0;
    }
    const int tag = (lt_mask << 15) + conn;
    if(calc_memo[x].count(tag)) return calc_memo[x][tag];

    const int MASK_PAT = 1 << H;
    LL ans = 0;
    for(int mask = 0; mask < MASK_PAT; ++mask) {
        const auto &np = calc_next(lt_mask, conn, mask);
        add(ans, calc(x+1, np.first, np.second));
    }
    return calc_memo[x][tag] = ans;
}

int main() {
    cin >> H >> W;
    cout << calc(0, 1, 0) << endl;
    return 0;
}
