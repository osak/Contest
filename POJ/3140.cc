//Name: Contestants Division
//Level: 4
//Category: グラフ,Graph,木
//Note:

/*
 * 問題文をよく見ると，入力は必ず木になることがわかる．
 * したがって，適当なノードを根にしてグラフ全体を木構造として順序づけておき，
 * 各ノードが自分とそれより下にあるノードの合計値を覚えておくような構造を作っておくと，
 * 全体を2つに分割することは枝を1本取り除くことと等価であるから
 *   上半分の合計 = S - subtotal[node]
 *   下半分の合計 = subtotal[node]
 * で求められる．
 *
 * オーダーは O(N+M)．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <limits>

using namespace std;

//#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define FOREACH(it,c) for(vector<int>::const_iterator it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

typedef long long LL;

int students[100000];
LL memo[100000];
int parent[100000];
vector<vector<int> > graph(100000);

void build(int pos) {
    memo[pos] = students[pos];
    FOREACH(it, graph[pos]) {
        if(parent[*it] == -2) {
            parent[*it] = pos;
            build(*it);
            memo[pos] += memo[*it];
        }
    }
}

int main() {
    int N, M;
    int CASE = 1;
    while(scanf("%d %d", &N, &M) != EOF) {
        if(!N && !M) break;
        LL sum = 0;
        TIMES(i, N) {
            scanf("%d", students+i);
            sum += students[i];
            graph[i].clear();
        }
        TIMES(i, M) {
            int a, b;
            scanf("%d %d", &a, &b);
            --a; --b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        fill_n(parent, N, -2);
        parent[0] = -1;
        build(0);
        LL ans = numeric_limits<LL>::max();
        TIMES(i, N) {
            const int node = i;
            if(parent[node] == -2) continue;
            const LL a = sum - memo[node];
            const LL b = memo[node];
            LL diff = a-b;
            if(diff < 0) diff = -diff;
            ans = min(ans, diff);
        }
        cout << "Case " << CASE << ": " << ans << endl;
        ++CASE;
    }
    return 0;
}
