//Name: 木
//Level: 4
//Category: 木,Tree,動的計画法,DP
//Note: Typical DP Contest N

/**
 *   o
 *  /|\
 * a c b
 * a: a本k通り
 * b: b本l通り
 * c: c本m通り
 * パターン数: (a+b+c+3)(C)(a+1) * (b+c+2)(C)(b+1) * k * l
 *
 * 最初に塗る辺を決め、上の式にしたがってパターン数を計算する。
 * ((C)はコンビネーション)
 * オーダーはO(N^2)。
 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;

const LL MOD = 1000000007;

LL comb[1003][1003];
void calc_comb() {
    comb[0][0] = 1;
    for(int n = 1; n <= 1002; ++n) {
        for(int k = 0; k <= n; ++k) {
            const LL prev = (k == 0) ? 0 : comb[n-1][k-1];
            comb[n][k] = (comb[n-1][k] + prev) % MOD;
        }
    }
}

pair<int,LL> calc(int pos, const vector<vector<int>> &tree, int root) {
    pair<int,LL> res(0, 1);
    for(int neigh : tree[pos]) {
        if(neigh != root) {
            pair<int,LL> tmp = calc(neigh, tree, pos);
            res.first += tmp.first + 1;
            res.second *= tmp.second;
            res.second %= MOD;
            res.second *= comb[res.first][tmp.first+1];
            res.second %= MOD;
        }
    }
    return res;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    calc_comb();

    int N;
    cin >> N;
    vector<vector<int>> tree(N);
    vector<pair<int,int>> edges;
    for(int i = 0; i < N-1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        tree[a].push_back(b);
        tree[b].push_back(a);
        edges.push_back(make_pair(a, b));
    }

    LL ans = 0;
    for(const auto &e : edges) {
        pair<int,LL> pa = calc(e.first, tree, e.second);
        pair<int,LL> pb = calc(e.second, tree, e.first);
        int en = pa.first + pb.first;
        LL pat = (comb[en][pa.first] * pa.second % MOD) * pb.second % MOD;
        ans += pat;
        ans %= MOD;
    }
    cout << ans << endl;
    return 0;
}
