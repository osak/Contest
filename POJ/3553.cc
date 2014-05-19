//Name: Task schedule
//Level: 3
//Category: 貪欲,Greedy
//Note:

/**
 * 依存関係がない場合、〆切の早いものから順に処理していけばよい。
 * 依存関係があると単純にはできないが、DAGの末端のほうにあっても〆切の早いものはなるべく早く片付けるべきなので、
 * 各頂点の〆切をmin(自分の〆切, 子の〆切)にして、依存関係が満たされたものから処理していくとうまくいく。
 * （厳密な証明はしていない。また、ジャッジデータがすごく弱い。）
 *
 * サンプルケース：
 * 3
 * 2 10
 * 1 100
 * 1 2
 * 1
 * 2 3
 *
 * オーダーは O(M + N log N)。
 */
#include <iostream>
#include <queue>

using namespace std;

typedef long long LL;

struct Edge {
    int from, to;
    bool operator <(const Edge &e) const {
        return from < e.from;
    }
};

int limit[50000];
bool visited[50000];
Edge edges[50000*10+10];
int start_of[50000];

int dfs(int v) {
    if(visited[v]) return limit[v];
    for(int i = start_of[v]; edges[i].from == v; ++i) {
        limit[v] = min(limit[v], dfs(edges[i].to));
    }
    visited[v] = true;
    return limit[v];
}

bool solve() {
    int N;
    if(scanf("%d", &N) == EOF) return false;
    if(!N) return false;
    static LL costs[50000];
    static int ref_cnt[50000];

    for(int i = 0; i < N; ++i) {
        scanf("%lld %d", &costs[i], &limit[i]);
    }
    int M;
    scanf("%d", &M);
    for(int i = 0; i < M; ++i) {
        scanf("%d %d", &edges[i].from, &edges[i].to);
        --edges[i].from;
        --edges[i].to;
        ref_cnt[edges[i].to]++;
    }
    sort(edges, edges+M);
    edges[M].from = -1;
    for(int i = 0; i < M; ++i) {
        if(i == 0 || edges[i].from != edges[i-1].from) {
            start_of[edges[i].from] = i;
        }
    }
    fill_n(visited, N, false);
    for(int i = 0; i < N; ++i) {
        if(ref_cnt[i] == 0) dfs(i);
    }

    priority_queue<pair<LL,int> > q;
    for(int i = 0; i < N; ++i) {
        if(ref_cnt[i] == 0) {
            q.push(make_pair(-limit[i], i));
        }
    }
    while(!q.empty()) {
        const int task = q.top().second;
        q.pop();
        printf("%d\n", task+1);
        for(int i = start_of[task]; edges[i].from == task; ++i) {
            const int to = edges[i].to;
            if(--ref_cnt[to] == 0) {
                q.push(make_pair(-limit[to], to));
            }
        }
    }
    return true;
}

int main() {
    while(solve()) ;
    return 0;
}
