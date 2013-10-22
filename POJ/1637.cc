//Name: Sightseeing tour
//Level: 3
//Category: グラフ,Graph,辺被覆,最大流
//Note:

/**
 * 有向辺を含むグラフで、オイラー路が存在するかを判定する問題。
 *
 * まず、Inputの最後の文より、全体が連結であることは保証されている。
 * したがって、各頂点の次数のみを考えて良い。
 * 問題となるのは入次数と出次数が釣り合っていない頂点だが、
 * これらの頂点は、入次数が足りないぶんだけ無向辺のtoになり、
 * 出次数が足りないぶんだけ無向辺のfromとなればよい。
 * これは、最大流問題として、出次数が足りないぶんだけスーパーソースからフローを流し込み、
 * 入次数が足りないぶんだけスーパーシンクから流れ出すようにした問題を解くことで、
 * 無向辺のスケジューリングができる。
 *
 * フローを流し終わったら、使われなかった辺がオイラー路の構成要件を満たしているか確認する。
 *
 * オーダーはO(S(S+M))。
 */
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int from, to;
    int cap, flow;
    Edge *back;
};

vector<Edge*> graph[202];
Edge _edges[5000];
int _eit;
int M;

void make_edge(int a, int b, int cap, bool bidi) {
    Edge *e1 = &_edges[_eit++];
    Edge *e2 = &_edges[_eit++];
    const int cap2 = bidi ? cap : 0;
    e1->from = a; e1->to = b; e1->cap = cap; e1->flow = 0; e1->back = e2;
    e2->from = b; e2->to = a; e2->cap = cap2; e2->flow = 0; e2->back = e1;
    graph[a].push_back(e1);
    graph[b].push_back(e2);
}

int maxflow(int source, int sink, int flow) {
    static Edge *came_by[202];
    int f = flow;
    while(f > 0) {
        for(int i = 0; i < M; ++i) {
            came_by[i] = NULL;
        }
        queue<int> q;
        q.push(source);
        while(!q.empty()) {
            const int cur = q.front();
            q.pop();
            if(cur == sink) {
                Edge *e = came_by[cur];
                int ff = INT_MAX;
                while(e) {
                    ff = min(ff, e->cap - e->flow);
                    e = came_by[e->from];
                }
                e = came_by[cur];
                while(e) {
                    e->flow += ff;
                    e->back->flow -= ff;
                    e = came_by[e->from];
                }
                e = came_by[cur];
                f -= ff;
                goto next;
            }
            const int E = graph[cur].size();
            for(int i = 0; i < E; ++i) {
                Edge *e = graph[cur][i];
                if(e->cap - e->flow > 0) {
                    if(e->to != source && came_by[e->to] == NULL) {
                        came_by[e->to] = e;
                        q.push(e->to);
                    }
                }
            }
        }
        break;
next:
        ;
    }
    return flow - f;
}

void solve() {
    int S;
    scanf("%d %d", &M, &S);
    static int degree[202][202];
    static int in[202], out[202];
    const int SOURCE = M;
    const int SINK = M+1;
    M += 2;
    for(int i = 0; i < M; ++i) {
        graph[i].clear();
        in[i] = out[i] = 0;
        for(int j = 0; j < M; ++j) {
            degree[i][j] = 0;
        }
    }
    _eit = 0;
    int flow = 0;
    for(int i = 0; i < S; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        --a; --b;
        if(c == 1) {
            out[a]++;
            in[b]++;
            ++flow;
        } else {
            degree[a][b]++;
            degree[b][a]++;
        }
    }
    for(int i = 0; i < M; ++i) {
        if(out[i]) make_edge(i, SINK, out[i], false);
        if(in[i]) make_edge(SOURCE, i, in[i], false);
        for(int j = 0; j < i; ++j) {
            if(degree[i][j]) make_edge(i, j, degree[i][j], true);
        }
    }
    const int actual = maxflow(SOURCE, SINK, flow);
    //printf("%d %d\n", flow, actual);
    if(actual != flow) {
        puts("impossible");
        return;
    }
    bool ok = true;
    for(int i = 0; i < SOURCE; ++i) {
        int deg = 0;
        const int E = graph[i].size();
        for(int j = 0; j < E; ++j) {
            const Edge *e = graph[i][j];
            if(e->cap > 0 && e->cap - e->flow > 0) {
                //printf("%d %d %d\n", e->from, e->to, e->cap-e->flow);
                deg += e->cap - e->flow;
            }
        }
        //printf("%d %d\n", i, deg);
        if(deg % 2 != 0) {
            ok = false;
            break;
        }
    }
    puts(ok ? "possible" : "impossible");
}

int main() {
    int N;
    scanf("%d", &N);
    while(N--) solve();
    return 0;
}
