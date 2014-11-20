//Name: Dangerous Tower
//Level: 4
//Category: グラフ,Graph,マッチング
//Note:

/**
 * 順番に関係なく、横方向の長さがすべて相異なるような集合を取り、それらの積み木で縦方向の長さを合計すれば塔の高さになる。
 * このとき、問題は以下のように変形できる。
 * ・横方向の長さwについて、対応する積み木を高々1つ選ぶ。
 * ・ある積み木が選ばれたとき、ちょうど1つだけ他の積み木が使用不能になる。
 * ・積み木を選ぶと、一定のスコアが得られる。この合計を最大化したい。
 * この問題は、以下のような3段からなるグラフを構成し、フローを1ずつ増やしながら最小費用になる点を求めれば解ける。
 *
 * ・ソースから1段目は、容量1、コスト0の辺で結ぶ。
 * ・1段目には、ある横方向の長さ1つにつき、対応する頂点を1つ作る（長さwに対応する頂点をv1_wとする）。
 * ・2段目には、各積み木に対し、縦に置いたときと横に置いた時のそれぞれに対応する頂点を作る（それぞれv2_{i,1}, v2_{i,2}とする）。
 * 　・v2_{i,1}は、頂点v1_Aと容量1、コスト-Bの辺で結ぶ（Aを横方向にしたときに対応）。
 * 　・v2_{i,2}は、頂点v1_Bと容量1、コスト-Aの辺で結ぶ（Bを横方向にしたときに対応）。
 * ・3段目には、積み木1つに対し頂点v3_iを作る。
 * 　・v2_{i,1}とv2_{i,2}とv3_iをそれぞれ容量1、コスト0の辺で結ぶ。
 * ・3段目とシンクは、容量1、コスト0の辺で結ぶ。
 *
 * 頂点数は、各段でO(N)頂点が作成されるので、全体でもO(N)個で抑えられる。
 * （定数としては、1段目は高々2N、2段目は2N、3段目はNなので、高々5N頂点）。
 *
 * Primal-Dualを用いると、このグラフでは1ずつしかフローが増えないため、毎回の更新処理の後で費用を記録しておけば
 * 求めたい値が得られる。
 * オーダーは O(|V|^2 U) 程度。
 * ただしUは辺容量の和で、U=O(N)。
 * すなわち、全体では O(N^3) 程度になる。
 */
#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

template<class Flow, class Cost>
struct Edge {
    int from, to;
    Flow capacity, flow;
    Cost cost;
    Edge *back;
    Edge() {}
    Edge(int from, int to, Flow c, Cost d, Edge *b) : from(from), to(to), capacity(c), flow(0), cost(d), back(b) {}
};

const long long INF = 1000000 * 1000 * 2;
template<class Flow, class Cost>
void make_edge(vector<vector<Edge<Flow,Cost>*>> &g, int src, int dst, Flow c, Cost d) {
    auto *e = new Edge<Flow,Cost>(src, dst, c, d, nullptr);
    auto *back = e->back = new Edge<Flow,Cost>(dst, src, 0, -d, e);
    g[src].push_back(e);
    g[dst].push_back(back);
}

template<class Flow, class Cost>
Cost primal_dual(vector<vector<Edge<Flow,Cost>*>> &g, int src, int sink, int max_flow) {
    const int N = g.size();
    pair<Flow, Cost> res;
    vector<Cost> h(N), dist(N);
    vector<Edge<Flow,Cost>*> parent(N);
    Cost ans = 0;
    for(Flow f = max_flow; f > 0; ) {
        fill(dist.begin(), dist.end(), INF);
        dist[src] = 0;
        fill(parent.begin(), parent.end(), nullptr);
        priority_queue<pair<Cost,int>> q;
        q.push(make_pair(0, src));
        while(!q.empty()) {
            const int n = q.top().second;
            const Cost c = -q.top().first;
            q.pop();
            if(dist[n] < c) {
                continue;
            }
            for(auto e : g[n]) {
                if(e->capacity - e->flow > 0) {
                    const Cost c2 = c + e->cost + h[n] - h[e->to];
                    if(c2 < dist[e->to]) {
                        dist[e->to] = c2;
                        parent[e->to] = e;
                        q.push(make_pair(-c2, e->to));
                    }
                }
            }
        }
        if(parent[sink] == nullptr) {
            break;
        }

        Flow to_push = f;
        for(int i = sink; i != src; i = parent[i]->from) {
            auto e = parent[i];
            to_push = min(to_push, e->capacity - e->flow);
        }
        for(int i = sink; i != src; i = parent[i]->from) {
            auto e = parent[i];
            res.second += to_push * e->cost;
            e->flow += to_push;
            e->back->flow -= to_push;
        }
        f -= to_push;
        res.first += to_push;
        for(int i = 0; i < N; ++i) {
            h[i] += dist[i];
        }
        ans = min(ans, res.second);
    }
    return ans;
}/*}}}*/

struct Dict {
    map<int,int> dict;

    int get(int i) {
        if(dict.count(i)) return dict[i];
        const int idx = dict.size();
        return dict[i] = idx;
    }
};

typedef Edge<int,long long> E;
bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<vector<E*>> graph(5*N+2);
    const int SRC = 5*N;
    const int SINK = SRC+1;

    Dict dict;
    for(int i = 0; i < N; ++i) {
        int a, b;
        cin >> a >> b;
        const int v1a = dict.get(a);
        const int v1b = dict.get(b);
        const int v2a = 2*N + i*2 + 0;
        const int v2b = 2*N + i*2 + 1;
        const int v3 = 4*N + i;
        make_edge(graph, v1a, v2a, 1, (long long)-b);
        make_edge(graph, v1b, v2b, 1, (long long)-a);
        make_edge(graph, v2a, v3, 1, 0LL);
        make_edge(graph, v2b, v3, 1, 0LL);
        make_edge(graph, v3, SINK, 1, 0LL);
    }
    for(const auto p : dict.dict) {
        make_edge(graph, SRC, p.second, 1, 0LL);
    }
    cout << -primal_dual(graph, SRC, SINK, 2*N) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
