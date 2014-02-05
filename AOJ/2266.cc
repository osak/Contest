//Name: Cache Strategy
//Level: 5
//Category: グラフ,Graph,最小費用流,Minimum Cost Flow
//Note:

/**
 * まず、次回の同じものが来るまで玉を入れっぱなしにしないのであれば、即座に取り出しても変わらないことが分かる。
 * 簡単のため、玉を取り出したときにコストがかかるものとする（一番最後に全ての玉を取り出して帳尻を合わせる）と、ある箱の状態遷移は
 * (1) 時刻tで玉を入れ、玉を取り出して時刻t+1に遷移する
 * (2) 時刻tで玉を入れず、時刻t+1に遷移する
 * (3) 時刻tで玉を入れ、次に同じ玉が必要になる時刻t'に遷移する
 * の3通りになる。
 * また、全ての時刻について、かならず1本だけ、玉を入れる遷移をたどる箱がなければならない。
 *
 * このような遷移をナイーブにグラフに落とすと
 * (1) v[t] -(1/w[v[t]])-> v[t+1]
 * (2) v[t] -(∞/0)-> v[t+1]
 * (3) v[t] -(0/1)-> v[t']
 * となる。ここで、必ず(1)か(3)に流量1を流さなければならないので、(3)を
 * (3') v[t] -(1/w[v[t]])-> v[t+1] -(1/-w[v[t]])-> v[t']
 * と変形することで、(1)と(3')をまとめて、全ての(1)の辺に流量1を流しておけばよくなる。
 *
 * この変形を行うと、オフセットを∑w[v[t]]とした上で
 * (2) v[t] -(∞/0)-> v[t+1]
 * (3'') v[t+1] -(1/-w[v[t]])-> v[t']
 * のグラフ上で、流量M-1の最小費用流を求める問題に帰着できる。
 * ただし、t+1 == t'のときは負閉路ができてしまうため、このような頂点はあらかじめ縮約しておく必要がある。
 *
 * オーダーはO(K^2 + MNK)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;
const LL BASE = 10000LL * 10000LL * 100;
const LL INF = 1LL << 59;

template<class Flow, class Cost>
struct Edge {
    int from, to;
    Flow cap, flow;
    Cost cost;
    Edge *back;

    Edge(int from, int to, Flow cap, Cost cost, Edge *back) : from(from), to(to), cap(cap), flow(0), cost(cost), back(back) {}
};

template<class Flow, class Cost>
void add_edge(vector<vector<Edge<Flow, Cost>*>> &g, int src, int dst, Flow c, Cost d) {
    Edge<Flow,Cost> *ea = new Edge<Flow,Cost>(src, dst, c, d, nullptr);
    Edge<Flow,Cost> *eb = new Edge<Flow,Cost>(dst, src, 0, -d, ea);
    ea->back = eb;
    g[src].push_back(ea);
    g[dst].push_back(eb);
}

template<class Flow, class Cost>
pair<Flow,Cost>
primal_dual(vector<vector<Edge<Flow,Cost>*>> &g, int src, int sink, Flow max_flow) {
    const int N = g.size();
    pair<Flow, Cost> res;
    vector<Cost> dist(N);
    vector<Edge<Flow,Cost>*> prev(N);
    for(Flow f = max_flow; f > 0; ) {
        fill(dist.begin(), dist.end(), INF);
        fill(prev.begin(), prev.end(), nullptr);
        dist[src] = 0;

        while(true) {
            bool updated = false;
            for(int i = 0; i < N; ++i) {
                for(auto *e : g[i]) {
                    if(e->cap - e->flow > 0) {
                        Cost nc = dist[e->from] + e->cost;
                        if(nc < dist[e->to]) {
                            dist[e->to] = nc;
                            prev[e->to] = e;
                            updated = true;
                        }
                    }
                }
            }
            if(!updated) break;
        }
        if(prev[sink] == nullptr) break;

        Flow aug = f;
        for(auto *e = prev[sink]; e; e = prev[e->from]) {
            aug = min(aug, e->cap - e->flow);
        }
        for(auto *e = prev[sink]; e; e = prev[e->from]) {
            res.second += aug * e->cost;
            e->flow += aug;
            e->back->flow -= aug;
        }
        f -= aug;
        res.first += aug;
    }

    return res;
}

bool solve() {
    int M, N, K;
    if(!(cin >> M >> N >> K)) return false;

    vector<LL> ws(N);
    vector<int> as;
    vector<vector<Edge<int,LL>*>> graph(K+2);
    const int SRC = K;
    const int SINK = K+1;
    for(int i = 0; i < N; ++i) {
        cin >> ws[i];
    }
    LL sum = 0;
    for(int i = 0; i < K; ++i) {
        int a;
        cin >> a;
        --a;
        if(as.size() > 0 && as.back() == a) {
            // do nothing
        } else {
            as.push_back(a);
            sum += ws[a];
        }
    }
    const int L = as.size();
    for(int i = 0; i < L; ++i) {
        // Edge to neighbor
        if(i+1 < L) {
            add_edge(graph, i, i+1, M, 0LL);
        }
        // Edge to next same number
        auto it = find(as.begin()+i+1, as.end(), as[i]);
        if(it != as.end()) {
            add_edge(graph, i+1, it-as.begin(), 1, -ws[as[i]]);
        }
    }
    add_edge(graph, SRC, 0, M, 0LL);
    add_edge(graph, L-1, SINK, M, 0LL);
    auto res = primal_dual(graph, SRC, SINK, M-1);
    cout << sum + res.second << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
