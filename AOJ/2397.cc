//Name: Three-way Branch
//Level: 3
//Category: 数え上げ,行列累乗
//Note:

/*
 * 障害物の手前までは行列の累乗で一気に飛ばせる．
 * 障害物のある行では，障害物の箇所のパターン数を0にする．
 *
 * オーダーは O(N W^3 log H) くらい．
 * 行列の乗算が O(W^3)，X乗が O(W^3 log X)でXは最大でH．
 *
 * 行方向の添字はすべてlong longで扱わないといけないことに注意．
 */
#ifndef ONLINE_JUDGE
//#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <utility>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

const int MOD = 1000000009;
void matmul(vector<vector<int> > &a, const vector<vector<int> > &b) {
    assert(a.size() > 0);
    assert(b.size() > 0);
    const int H = a.size();
    const int W = b[0].size();
    const int K = b.size();
    assert(K == (int)a[0].size());

    vector<vector<int> > res(H, vector<int>(W, 0));
    TIMES(r, H) {
        TIMES(c, W) {
            long long tmp = 0;
            TIMES(k, K) {
                tmp += static_cast<long long>(a[r][k]) * b[k][c];
                tmp %= MOD;
            }
            res[r][c] = static_cast<int>(tmp);
        }
    }
    a.swap(res);
}

void matvec(const vector<vector<int> > &m, vector<int> &v) {
    assert(m.size() > 0);
    const int H = m.size();
    const int W = m[0].size();
    assert(W == (int)v.size());

    vector<int> res(H, 0);
    TIMES(r, H) {
        long long tmp = 0;
        TIMES(c, W) {
            tmp += static_cast<long long>(m[r][c]) * v[c];
            tmp %= MOD;
        }
        res[r] = static_cast<int>(tmp);
    }
    v.swap(res);
}

vector<vector<int> > matpow(const vector<vector<int> > &a, long long x) {
    const int N = a.size();
    assert(N == (int)a[0].size());

    if(x == 0) {
        vector<vector<int> > res(N, vector<int>(N, 0));
        TIMES(i, N) {
            res[i][i] = 1;
        }
        return res;
    } else if(x == 1) {
        return a;
    } else {
        vector<vector<int> > half = matpow(a, x/2);
        vector<vector<int> > res = half;
        matmul(res, half);
        if(x % 2 == 1) matmul(res, a);
        return res;
    }
}

long long W, H, N;
void solve(int CASE) {
    vector<pair<long long,int> > obstacles(N);
    TIMES(i, N) {
        cin >> obstacles[i].second >> obstacles[i].first;
        --obstacles[i].second;
    }
    sort(obstacles.begin(), obstacles.end());

    vector<int> vec(W, 0);
    vector<vector<int> > mat(W, vector<int>(W, 0));
    TIMES(r, W) {
        if(r > 0) mat[r][r-1] = 1;
        mat[r][r] = 1;
        if(r+1 < W) mat[r][r+1] = 1;
    }

    vec[0] = 1;
    long long cur = 1;
    int pos = 0;
    while(pos < N && obstacles[pos].first == cur) ++pos;
    while(pos < N) {
        const long long next_depth = obstacles[pos].first;
        const long long x = next_depth - cur - 1;
        assert(x >= 0);
        vector<vector<int> > mm = matpow(mat, x);
        matvec(mm, vec);
        vector<int> next_vec(W, 0);
        TIMES(c, W) {
            if(pos < N && obstacles[pos] == make_pair(next_depth, c)) {
                ++pos;
            } else {
                long long tmp = 0;
                if(c > 0) tmp += vec[c-1];
                tmp += vec[c];
                if(c+1 < W) tmp += vec[c+1];
                next_vec[c] = tmp % MOD;
            }

        }
        vec.swap(next_vec);
        cur = next_depth;
    }
    // Last
    if(cur < H) {
        const long long x = H - cur;
        vector<vector<int> > mm = matpow(mat, x);
        matvec(mm, vec);
    }
    cout << "Case " << CASE << ": " << vec[W-1] << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int CASE = 1;
    while(true) {
        cin >> W >> H >> N;
        if(!H && !W && !N) break;
        solve(CASE++);
    }
    return 0;
}
