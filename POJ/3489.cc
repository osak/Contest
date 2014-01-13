//Name: Knapsack I
//Level: 4
//Category: 数学
//Note:

/**
 * 荷物を無限に分割できるので、XK^aを作る問題に還元できる。
 * 荷物のgcdが1であれば、aを十分大きく取れば必ず作れる。
 * そうでない場合、K^a ≡ 0なるaが存在するかという判定になるが、これは K ≡ gcd と等価である。
 *
 * オーダーはO(N log V)。
 * ただしVは荷物の最大値。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

int gcd(int a, int b) {
    if(a < b) swap(a, b);
    while(b) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

bool solve() {
    int N, X, K;
    if(scanf("%d %d %d", &N, &X, &K) == EOF) return false;
    if(!N && !X && !K) return false;

    int gcd_val = 0;
    TIMES(i, N) {
        int v;
        scanf("%d", &v);
        if(i == 0) {
            gcd_val = v;
        } else {
            gcd_val = gcd(gcd_val, v);
        }
    }
    bool ok = true;
    if(gcd_val > 1) {
        if(K % gcd_val != 0) ok = false;
    }
    puts(ok ? "Yes" : "No");
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
