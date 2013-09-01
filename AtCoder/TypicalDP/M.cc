//Name: 家
//Level: 4
//Category: DP,動的計画法,TSP,巡回セールスマン問題
//Note: Typical DP Contest M

/*
 * 1つの階で部屋iからjへ移動するパターン数は、TSPを解くことによって計算できる。
 * これによってa_{ij} = (部屋iから部屋jへ移動するパターン数)の行列が得られるので、
 * この行列をH乗することで解が得られる。
 *
 * オーダーはO(2^R R^3 * log H)。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long LL;

const LL MOD = 1000000007LL;
LL dp[1<<16][16];
bool G[16][16];
int R;

vector<LL> tsp(int start) {
    fill_n((int*)dp, sizeof(dp)/sizeof(int), 0);
    dp[1<<start][start] = 1;
    for(int pat = 0; pat < (1<<R); ++pat) {
        for(int cur = 0; cur < R; ++cur) {
            if(!(pat & (1<<cur))) continue;
            for(int prev = 0; prev < R; ++prev) {
                if(!G[prev][cur]) continue;
                if(!(pat & (1<<prev))) continue;
                dp[pat][cur] += dp[pat & ~(1<<cur)][prev];
                dp[pat][cur] %= MOD;
                //cout << pat << ' ' << cur << ' ' << dp[pat][cur] << endl;
            }
        }
    }
    vector<LL> vec(R, 0);
    for(int pat = 0; pat < (1<<R); ++pat) {
        for(int cur = 0; cur < R; ++cur) {
            vec[cur] += dp[pat][cur];
            vec[cur] %= MOD;
        }
    }
    return vec;
}

void matmul(vector<vector<LL> > &a, const vector<vector<LL> > &b) {
    const int A = a.size();
    const int B = a[0].size();
    const int C = b[0].size();
    assert(B == b.size());

    vector<vector<LL> > res(A, vector<LL>(C, 0));
    for(int i = 0; i < A; ++i) {
        for(int j = 0; j < C; ++j) {
            for(int k = 0; k < B; ++k) {
                res[i][j] += a[i][k] * b[k][j];
                res[i][j] %= MOD;
            }
        }
    }
    a.swap(res);
}

ostream& operator <<(ostream &os, const vector<LL> &v) {
    os << "[";
    bool first = true;
    for(LL l : v) {
        if(!first) os << ", ";
        os << l;
        first = false;
    }
    os << "]";
    return os;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int H;
    cin >> H >> R;
    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < R; ++j) {
            cin >> G[i][j];
        }
    }

    vector<vector<LL> > base_mat(R);
    for(int i = 0; i < R; ++i) {
        base_mat[i] = tsp(i);
        //cout << base_mat[i] << endl;
    }
    vector<vector<LL> > E(R, vector<LL>(R, 0));
    for(int i = 0; i < R; ++i) {
        E[i][i] = 1;
    }
    vector<vector<LL> > ans = E;
    vector<vector<LL> > factor = base_mat;
    while(H) {
        if(H & 1) {
            matmul(ans, factor);
        }
        matmul(factor, factor);
        H >>= 1;
    }
    cout << ans[0][0] << endl;
    return 0;
}
