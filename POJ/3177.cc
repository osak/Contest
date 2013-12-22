//Name: Redundant Paths
//Level: 3
//Category: グラフ,Graph,橋分解
//Note: 

/**
 * 任意の頂点間に2つ以上の経路があるということは、どの辺を取り除いてもグラフが連結であるということと等しい。
 * このような性質をbiconnectedという。
 *
 * 削除するとグラフが非連結になるような辺を橋といい、TarjanのアルゴリズムによってO(V+E)で列挙することができる。
 * 橋を通らない経路があるような頂点間では、必ず2つ以上の経路が存在することは容易にわかる。
 * したがって、橋をなくすことを考える。
 *
 * 強連結成分分解と同様の考え方によって、biconnectedな部分集合を1頂点に縮約し、このような頂点と橋のみからなるグラフが構成できる。
 * このとき、このグラフは木になることがわかる。
 * このグラフの上に辺を加えてループを構成すると、それに関わる橋はすべて橋でなくなる。
 * また、木であるから、このようなループは最低でもceil(葉の数/2)だけ必要である。
 * 実際、LCAが根であるような2つの葉を選んで辺を張ることを繰り返すと、この最低数を達成できる。
 * （ただし、全ての葉が根についている場合を除き、根に付いている葉のみを選ぶ操作は行ってはいけない）
 *
 * また、Tarjanのアルゴリズムでは多重辺のうち1本が橋として検出されることがある。
 * 縮約するときにはこのような辺の存在に注意する必要がある。
 *
 * オーダーはO(F+R)。
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

struct Edge {
    int from, to;
    bool bridge;
    Edge *back;
};

bool cmp(const Edge *e1, const Edge *e2) {
    return e1->from < e2->from;
}

Edge _edges[20010];
int _pos;
Edge *edges[20010];
int start_of[5005];

pair<Edge*, Edge*> make_edge(int a, int b) {
    Edge *ea = &_edges[_pos++];
    Edge *eb = &_edges[_pos++];
    ea->from = eb->to = a;
    eb->from = ea->to = b;
    ea->bridge = eb->bridge = false;
    ea->back = eb;
    eb->back = ea;
    return make_pair(ea, eb);
}

void dfs(int pos, int prev, int *low, int *ord, vector<int> &buf, int &cnt) {
    ord[pos] = cnt++;
    low[pos] = ord[pos];
    if(start_of[pos] == -1) return;
    for(int i = start_of[pos]; edges[i]->from == pos; ++i) {
        const int next = edges[i]->to;
        if(ord[next] == -1) {
            dfs(next, pos, low, ord, buf, cnt);
            low[pos] = min(low[pos], low[next]);
            if(low[next] == ord[next]) {
                buf.push_back(i);
                edges[i]->bridge = edges[i]->back->bridge = true;
            }
        } else if(next != prev) {
            low[pos] = min(low[pos], ord[next]);
        }
    }
}

int low[5005];
int ord[5005];
void bridges(vector<int> &buf, int N) {
    fill_n(low, N, -1);
    fill_n(ord, N, -1);
    int cnt = 0;
    TIMES(i, N) {
        if(ord[i] == -1) {
            dfs(i, -1, low, ord, buf, cnt);
        }
    }
}

int edge_count[5000][5000];

int paint(int pos, int *color) {
    int bridge_cnt = 0;
    if(start_of[pos] == -1) return 0;
    for(int i = start_of[pos]; edges[i]->from == pos; ++i) {
        const int next = edges[i]->to;
        if(!edges[i]->bridge && color[next] == -1) {
            color[next] = color[pos];
            bridge_cnt += paint(next, color);
        }
        if(edge_count[pos][next] == 1 && edges[i]->bridge) ++bridge_cnt;
    }
    return bridge_cnt;
}

bool solve() {
    int F, R;
    if(scanf("%d %d", &F, &R) == EOF) return false;
    if(!F && !R) return false;
    TIMES(i, F) {
        TIMES(j, F) {
            edge_count[i][j] = 0;
        }
    }
    _pos = 0;
    TIMES(i, R) {
        int a, b;
        scanf("%d %d", &a, &b);
        --a; --b;
        pair<Edge*, Edge*> ep = make_edge(a, b);
        edges[i*2] = ep.first;
        edges[i*2+1] = ep.second;
        edge_count[a][b]++;
        edge_count[b][a]++;
    }
    {
        pair<Edge*, Edge*> ep = make_edge(F, F);
        edges[R*2] = ep.first;
        edges[R*2+1] = ep.second;
    }
    if(F == 1) {
        printf("%d\n", max(0, 2-R));
        return true;
    }
    sort(edges, edges+R*2+2, cmp);
    fill_n(start_of, F, -1);
    TIMES(i, R*2) {
        if(i == 0) {
            start_of[edges[i]->from] = i;
        } else {
            if(edges[i-1]->from != edges[i]->from) {
                start_of[edges[i]->from] = i;
            }
        }
    }
    vector<int> buf;
    bridges(buf, F);
    /*
    TIMES(i, buf.size()) {
        printf("%d->%d\n", edges[buf[i]]->from+1, edges[buf[i]]->to+1);
    }
    */

    static int color[5005];
    fill_n(color, F, -1);
    int color_cnt = 0;
    int leaf_cnt = 0;
    TIMES(i, F) {
        if(color[i] == -1) {
            color[i] = color_cnt++;
            if(paint(i, color) == 1) ++leaf_cnt;
        }
    }
    printf("%d\n", (leaf_cnt+1)/2);
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
