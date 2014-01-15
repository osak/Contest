//Name: Ranking the Cows
//Level: 2
//Category: グラフ,Graph,DAG,到達可能性判定
//Note:

/**
 * 大小関係はDAGになる。
 * iとjの大小関係は、DAGをたどって到達可能なときには定義されているが、それ以外のときは未定義である。
 * したがって、求める答えは到達不可能な頂点の組の個数となる。
 *
 * ある頂点間にパスが存在するかどうかは、DAG性を利用することで効率的に前計算できる。
 * まず、入次数が0の頂点iから出ている辺をたどり、直接の子jに対して、頂点iに到達可能な頂点からjへ到達可能であるという印を付ける。
 * たどられた辺は消去し、これによって入次数が0になった頂点は更にたどっていく。
 *
 * オーダーはO((M+N)N + N^2)。
 * 以下の実装では、到達可能かどうかをbitsetでもっているため更新処理が速く、O((M+N) log N + N^2)になっている。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <bitset>
#include <queue>
#include <list>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

list<int> graph[1000];
int degree[1000];
bitset<1000> reachable[1000];

bool solve() {
    int N, M;
    if(scanf("%d %d", &N, &M) == EOF) return false;
    if(!N && !M) return false;

    TIMES(i, N) {
        graph[i].clear();
        degree[i] = 0;
    }
    TIMES(_, M) {
        int x, y;
        scanf("%d %d", &x, &y);
        --x; --y;
        graph[x].push_back(y);
        degree[y]++;
    }

    queue<int> q;
    TIMES(i, N) {
        if(degree[i] == 0) q.push(i);
        reachable[i][i] = true;
    }
    while(!q.empty()) {
        const int cur = q.front();
        q.pop();
        for(list<int>::const_iterator it = graph[cur].begin(); it != graph[cur].end(); ++it) {
            reachable[*it] |= reachable[cur];
            if(--degree[*it] == 0) {
                q.push(*it);
            }
        }
    }
    int ans = 0;
    TIMES(i, N) {
        TIMES(j, i) {
            if(!reachable[i][j] && !reachable[j][i]) ++ans;
        }
    }
    printf("%d\n", ans);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
