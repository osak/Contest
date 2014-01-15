//Name: Gold Balanced Lineup
//Level: 3
//Category: 累積和,ハッシュ
//Note:

/**
 * 各ビットごとに累積和を取る。
 * このとき、ある区間[a, b]の全てのビットで立っている数が等しいということは、
 * acc[b][k] - acc[a-1][k]が全てのkで等しいということである。
 * これは、acc[b][k+1]-acc[b][k]が全てのkで等しいということと等価である。
 * したがって、このような配列を作り、ハッシュ化しておくことで、ある配列に対して対応する最小のインデックスが求められる。
 *
 * オーダーはO(NK + N log N)。
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
const LL PR1 = 1000000007;
const LL PR2 = 999983;

LL hash_one(int *v, int N, LL pr) {
    LL res = 0;
    TIMES(i, N-1) {
        res *= pr;
        res += v[i+1] - v[i];
    }
    return res;
}

pair<LL,LL> hashv(int *v, int N) {
    return make_pair(hash_one(v, N, PR1), hash_one(v, N, PR2));
}

int acc[100000][30];

bool solve() {
    int N, K;
    if(scanf("%d %d", &N, &K) == EOF) return false;
    if(!N && !K) return false;
    TIMES(i, N) {
        unsigned v;
        scanf("%u", &v);
        TIMES(j, K) {
            acc[i][j] = i > 0 ? acc[i-1][j] : 0;
            if(v & 1) acc[i][j]++;
            v >>= 1;
        }
    }
    map<pair<LL,LL>, int> h;
    h[make_pair(0, 0)] = -1;
    int ans = 0;
    TIMES(i, N) {
        const pair<LL,LL> tag = hashv(acc[i], K);
        //printf("%d %d %d\n", i, acc[i][0], acc[i][1]);
        //printf("%d %lld %lld\n", i, tag.first, tag.second);
        if(h.count(tag) == 0) {
            h[tag] = i;
        } else {
            ans = max(ans, i - h[tag]);
        }
    }
    printf("%d\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
