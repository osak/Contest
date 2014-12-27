//Name: Little Pony and Harmony Chest
//Level: 3
//Category: グラフ,Graph,最短経路,Shortest path
//Note:

/**
 * You can place any numbers of 1s.
 * Considering this attribute and the range of a_i, b_i will be at most 58 (putting 1 will always better than >58).
 *
 * To make all pairs coprime, no two b_i share the same prime factor.
 * Since b_i is at most 58, there are only 16 primes which can be the factor of b_i.
 * Then you can determine b_i from i=1 to N, memorizing which primes are already used (by bitmask) and what the score would be.
 * This will be a kind of shortest-path problem.
 *
 * This algorithm runs in O(2^P M log N), where
 *   - P is the number of primes, which is 16 in this problem.
 *   - M is the limit of b_i, which is 58.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>

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

int gcd(int a, int b) {
    if(a < b) swap(a, b);
    while(b) {
        const int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

const int PRIMES[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
bool solve() {
    int N;
    if(!(cin >> N)) return false;

    vector<int> as(N);
    for(int i = 0; i < N; ++i) {
        cin >> as[i];
    }

    vector<int> tbl(60, 0);
    for(int i = 0; i <= 58; ++i) {
        for(int j = 0; j < sizeof(PRIMES)/sizeof(int); ++j) {
            if(i % PRIMES[j] == 0) tbl[i] |= (1 << j);
        }
    }

    typedef unsigned char byte;
    vector<vector<Maybe<int>>> memo(N+1, vector<Maybe<int>>(1<<(sizeof(PRIMES)/sizeof(int))));
    vector<vector<tuple<int,byte>>> hist(N+1, vector<tuple<int,byte>>(1<<(sizeof(PRIMES)/sizeof(int))));

    priority_queue<tuple<int,int,int>> q;
    q.push(make_tuple(0, 0, 0));
    int best_pat = 0;
    while(!q.empty()) {
        int cost, pat, idx;
        tie(cost, pat, idx) = q.top();
        cost *= -1;
        q.pop();

        if(idx == N) {
            best_pat = pat;
            break;
        }
        if(memo[idx][pat].valid && cost > memo[idx][pat].val) continue;

        for(int i = 1; i <= 58; ++i) {
            if(pat & tbl[i]) continue;
            const int nc = cost + abs(as[idx] - i);
            const int np = pat | tbl[i];
            if(!memo[idx+1][np].valid || memo[idx+1][np].val > nc) {
                memo[idx+1][np] = nc;
                hist[idx+1][np] = make_tuple(pat, i);
                q.push(make_tuple(-nc, np, idx+1));
            }
        }
    }
    vector<int> v;
    for(int i = N; i > 0; --i) {
        int pat, val;
        tie(pat, val) = hist[i][best_pat];
        v.push_back(val);
        best_pat = pat;
    }
    reverse(begin(v), end(v));
    for(int i = 0; i < N; ++i) {
        if(i > 0) cout << ' ';
        cout << v[i];
    }
    cout << endl;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while(solve()) ;
    return 0;
}
