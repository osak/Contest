//Name: Fence Repair
//Level: 3
//Category: 貪欲,Greedy,Priority queue
//Note:

/**
 * 木構造にしてバラバラの葉をマージしていく問題としてみると、葉のコストはその深さが重みとして最終スコアにかかってくる。
 * したがって、最適解において、最も小さい2つの葉が一番深いところにあるはずである。
 * これをマージしたひとつ小さい問題についても同じことが言えるので、Priority queueで毎回小さい2つの葉を取り出していけばよい。
 *
 * オーダーはO(N log N)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

bool solve() {
    int N;
    if(scanf("%d", &N) == EOF) return false;
    if(!N) return false;

    priority_queue<long long> q;
    TIMES(i, N) {
        int v;
        scanf("%d", &v);
        q.push(-v);
    }
    long long ans = 0;
    TIMES(_, N-1) {
        long long a = -q.top();
        q.pop();
        long long b = -q.top();
        q.pop();
        ans += a+b;
        q.push(-a-b);
    }
    printf("%lld\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
