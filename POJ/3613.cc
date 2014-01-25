//Name: Cow Relays
//Level: 3
//Category: グラフ,Graph
//Note:

/**
 * 加算をmin、乗算を+とした体で考えると、距離行列のN乗はN頂点からなるパスの最短長をを求めることと等しい。
 * これは繰り返し二乗法によって高速に求めることができる。
 *
 * オーダーはO(T^3 log N)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

typedef long long LL;

const LL INF = 1LL<<50;
struct Dict {
    map<int,int> dict;

    int get(int key) {
        if(dict.count(key)) return dict[key];
        const int idx = dict.size();
        return dict[key] = idx;
    }

    int size() const {
        return dict.size();
    }
};

void matmul(vector<vector<LL> > &a, const vector<vector<LL> > &b) {
    const int R = a.size();
    const int C = b[0].size();
    const int K = a[0].size();
    vector<vector<LL> > res(R, vector<LL>(C, INF));
    TIMES(i, R) {
        TIMES(j, C) {
            LL tmp = INF;
            TIMES(k, K) {
                tmp = min(tmp, a[i][k] + b[k][j]);
            }
            res[i][j] = tmp;
        }
    }
    a.swap(res);
}

void print_mat(vector<vector<LL> > &v) {
    const int R = v.size();
    const int C = v[0].size();
    TIMES(i, R) {
        TIMES(j, C) {
            printf("%2lld ", v[i][j] == INF ? -1 : v[i][j]);
        }
        puts("");
    }
}

bool solve() {
    int N, T, S, E;
    if(scanf("%d %d %d %d", &N, &T, &S, &E) == EOF) return false;
    vector<vector<LL> > mat(2*T, vector<LL>(2*T, INF));
    Dict dict;
    TIMES(i, T) {
        int l, a, b;
        scanf("%d %d %d", &l, &a, &b);
        a = dict.get(a);
        b = dict.get(b);
        mat[a][b] = mat[b][a] = l;
    }
    dict.get(S);
    dict.get(E);
    T = dict.size();
    mat.resize(T);
    TIMES(i, T) {
        mat[i].resize(T);
    }
    vector<vector<LL> > res(T, vector<LL>(T, INF));
    TIMES(i, T) {
        res[i][i] = 0;
    }
    //print_mat(mat);
    //print_mat(res);
    while(N) {
        if(N & 1) {
            matmul(res, mat);
        }
        matmul(mat, mat);
        N >>= 1;
    }
    //print_mat(res);
    printf("%lld\n", res[dict.get(S)][dict.get(E)]);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
