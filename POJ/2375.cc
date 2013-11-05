//Name: Cow Ski Area
//Level: 3
//Category: グラフ,Graph,強連結成分分解
//Note: TLE厳しい

/**
 * 全体を強連結なグラフにする問題。
 *
 * このグラフを強連結成分分解したDAG上で考えると、
 * 始点と終点の間で適当に辺を張ってやれば、全体を行き来することができるようになる。
 *
 * このとき、全体が巡回するように辺を張ることで、条件を満たす。
 * このために必要な辺の本数は、始点の合計数と終点の合計数のうち、多い方の
 * 数と等しい。
 * これが最小であることは自明である。
 *
 * POJではTLEが厳しいので、強連結成分分解のトポロジカルソートを再帰で実装すると
 * TLEしてしまう。
 * したがって、自分でスタックを作り、再帰をシミュレーションしてやる必要がある。
 *
 * オーダーはO(WL)。
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

const int MAX = 500*500;

int graph[MAX][5];
int graph_n[MAX];
int rev_graph[MAX][5];
int rev_graph_n[MAX];
int field[500][500];
const int DR[] = {0, -1, 0, 1};
const int DC[] = {1, 0, -1, 0};
bool visited[MAX];
int labels[MAX];
bool is_head[MAX], is_tail[MAX];
stack<pair<int,int> > stk;

inline bool in_range(int a, int x, int b) {
    return a <= x && x < b;
}

// Number the nodes by post-order
void dfs1(int pos, vector<int> &ord) {
    stk.push(make_pair(pos, 1));
    stk.push(make_pair(pos, 0));
    visited[pos] = true;
    while(!stk.empty()) {
        const int cur = stk.top().first;
        const int phase = stk.top().second;
        stk.pop();
        if(phase == 1) {
            ord.push_back(cur);
        } else {
            visited[cur] = true;
            const int N = graph_n[cur];
            for(int i = 0; i < N; ++i) {
                if(!visited[graph[cur][i]]) {
                    stk.push(make_pair(graph[cur][i], 1));
                    stk.push(make_pair(graph[cur][i], 0));
                    visited[graph[cur][i]] = true;
                }
            }
        }
    }
}

// Label connected nodes
void dfs2(int pos, int l) {
    stk.push(make_pair(pos, 0));
    visited[pos] = true;
    labels[pos] = l;
    while(!stk.empty()) {
        const int cur = stk.top().first;
        stk.pop();
        const int N = rev_graph_n[cur];
        for(int i = 0; i < N; ++i) {
            if(!visited[rev_graph[cur][i]]) {
                visited[rev_graph[cur][i]] = true;
                labels[rev_graph[cur][i]] = l;
                stk.push(make_pair(rev_graph[cur][i], 0));
            }
        }
    }
}

int scc(int N) {
    vector<int> ord;
    fill_n(visited, N, false);
    for(int i = 0; i < N; ++i) {
        if(!visited[i]) dfs1(i, ord);
    }
    reverse(ord.begin(), ord.end());
    fill_n(visited, N, false);
    int l = 0;
    for(int i = 0; i < N; ++i) {
        if(!visited[ord[i]]) dfs2(ord[i], l++);
    }
    return l;
}

bool solve() {
    int W, L;
    if(scanf("%d %d", &W, &L) == EOF) return false;
    TIMES(r, L) {
        TIMES(c, W) {
            scanf(" %d", &field[r][c]);
            graph_n[r*W+c] = 0;
            rev_graph_n[r*W+c] = 0;
        }
    }
    TIMES(r, L) {
        TIMES(c, W) {
            const int id = r*W+c;
            TIMES(dir, 4) {
                const int nr = r + DR[dir];
                const int nc = c + DC[dir];
                if(!in_range(0, nr, L) || !in_range(0, nc, W)) continue;
                const int nid = nr*W+nc;
                if(field[r][c] >= field[nr][nc]) {
                    graph[id][graph_n[id]++] = nid;
                }
                if(field[r][c] <= field[nr][nc]) {
                    rev_graph[id][rev_graph_n[id]++] = nid;
                }
            }
        }
    }

    const int LN = scc(W*L);
    if(LN == 1) {
        puts("0");
        return true;
    }
    fill_n(is_head, MAX, true);
    fill_n(is_tail, MAX, true);
    for(int i = 0; i < W*L; ++i) {
        const int N = graph_n[i];
        const int li = labels[i];
        for(int j = 0; j < N; ++j) {
            const int lj = labels[graph[i][j]];
            if(lj != li) {
                is_head[lj] = false;
                is_tail[li] = false;
            }
        }
    }
    int heads = 0, tails = 0;
    for(int i = 0; i < LN; ++i) {
        if(is_head[i]) ++heads;
        else if(is_tail[i]) ++tails;
    }
    //printf("%d %d\n", heads, tails);
    printf("%d\n", max(heads, tails));
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
