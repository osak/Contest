//Name: Stripies
//Level: 2
//Category: 貪欲,Greedy
//Note:

/**
 * 大きい方から順にマージしていけばよい。
 * 0-indexedで考えると、マージ後の重さは
 *   x_0^(1/2^{N-1}) Π2^{N-k} x_k^(1/2^{N-k})
 * として表すことができる。
 * ここで x_k < x_{k+1} とすると、これを交換して比を取ると1より大きくなるため、交換したほうが有利であることが分かる。
 * したがって、この最適化を繰り返すと全体をバブルソートすることになり、解が得られる。
 *
 * オーダーは O(N log N)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

bool solve() {
    int N;
    if(scanf("%d", &N) == EOF) return false;
    vector<int> v;
    TIMES(_, N) {
        int x;
        scanf("%d", &x);
        v.push_back(x);
    }
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    if(N == 1) {
        printf("%d.000\n", v[0]);
    } else {
        double cur = 2*sqrt(v[0]*v[1]);
        for(int i = 2; i < N; ++i) {
            cur = 2*sqrt(cur*v[i]);
        }
        printf("%.3f\n", cur);
    }
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
