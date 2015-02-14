//Name: Fox And Dinner
//Level: 3
//Category: グラフ,Graph,二部グラフ
//Note: 

/**
 * Since all primes except 2 are odd, the neighboring numbers must be
 * one odd and one even (note that a_i >= 2).
 * This results in bipartite graph.
 * Our goal is to decompose this graph into circular graphs.
 *
 * All vertices in circular graph has degree of 2, and in this problem,
 * all vertices in given graph would have just degree of 2 in decomposed graph.
 * We can use bipartity of given graph, putting 2 units of flow into each left
 * node and pull 2 units of flow from each right node.
 * If 2*N flow can be pushed into the graph the edges with flow must form
 * circular graphs, because considering only edges with flow, all vertices has
 * degree of 2.
 *
 * The algorithm described above runs in O(N^2).
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

// Sieve of eratosthenes.
// Runs in O(N log log N).
vector<bool> eratosthenes(int N) {
    vector<bool> is_prime(N+1, true);
    is_prime[0] = is_prime[1] = false;

    const int LIM = static_cast<int>(sqrt(N));
    for(long long i = 2; i <= LIM; ++i) {
        if(is_prime[i]) {
            for(long long j = i*i; j <= N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

// Dinic's algorithm.
// This solves maximum flow problem efficiently.
// Runs in O(V^2 E)
// (In practice, this algorithm is faster than expected from theoretical analysis.)
//
template<typename T, T INF, bool directed=true>
struct Dinic {
    struct Edge {
        int to;
        T cap, flow;
        Edge *back;
        Edge(int to, T cap, T flow, Edge *back) : to(to), cap(cap), flow(flow), back(back) {}

        bool remain() const {
            return flow < cap;
        }

        void add_flow(T f) {
            flow += f;
            back->flow -= f;
        }
    };

    vector<vector<Edge*>> g_;
    vector<int> memo_, level_;
    int src_, sink_;

    Dinic(int N, int src, int sink) : g_(N), memo_(N), level_(N), src_(src), sink_(sink) {}
    ~Dinic() {
        for (auto &row : g_) {
            for (auto e : row) {
                delete e;
            }
        }
    }

    T dinic_augment(int v, T cap) {
        if(v == sink_) return cap;

        const int N = g_[v].size();
        for(int i = memo_[v]; i < N; ++i) {
            const auto &e = g_[v][i];
            if(level_[e->to] != level_[v]+1) continue;
            if(!e->remain()) continue;
            const T f = dinic_augment(e->to, min(cap, e->cap - e->flow));
            if(f > 0) {
                e->add_flow(f);
                memo_[v] = i+1;
                return f;
            }
        }
        return 0;
    }

    void add_edge(int from, int to, T cap) {
        //cout << from << ' ' << to << endl;
        Edge *e = new Edge(to, cap, 0, nullptr);
        Edge *r = new Edge(from, directed ? 0 : cap, 0, e);
        e->back = r;
        g_[from].push_back(e);
        g_[to].push_back(r);
    }

    T calc() {
        T flow = 0;
        while(true) {
            // Calculate depth of each vertex
            fill(begin(level_), end(level_), -1);
            queue<int> q;
            q.push(src_);
            level_[src_] = 0;
            while(!q.empty()) {
                const int v = q.front();
                q.pop();
                for (const auto &e : g_[v]) {
                    if(e->remain() && level_[e->to] == -1) {
                        level_[e->to] = level_[v] + 1;
                        q.push(e->to);
                    }
                }
            }

            // Search for the residual path of shortest length
            bool updated = false;
            fill(begin(memo_), end(memo_), 0);
            while(true) {
                T add = dinic_augment(src_, INF);
                if(add == 0) break;
                flow += add;
                updated = true;
            }
            if(!updated) break;
        }
        return flow;
    }
};

// ostream support for vector.
template<typename T>
ostream& operator <<(ostream &os, const vector<T> &v) {
    bool first = true;
    for(const T &t : v) {
        if(!first) cout << ' ';
        os << t;
        first = false;
    }
    return os;
}

vector<bool> is_prime = eratosthenes(20000);

bool solve(bool first) {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<int> nodes(N);
    for(int i = 0; i < N; ++i) {
        cin >> nodes[i];
    }

    Dinic<int,10000> dinic(N+2, N, N+1);
    int flow = 0;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < i; ++j) {
            if(is_prime[nodes[i] + nodes[j]]) {
                if(nodes[i] % 2 == 0) dinic.add_edge(i, j, 1);
                else dinic.add_edge(j, i, 1);
            }
        }
        if(nodes[i] % 2 == 0) {
            dinic.add_edge(N, i, 2);
            flow += 2;
        } else {
            dinic.add_edge(i, N+1, 2);
        }
    }
    if(flow != N || dinic.calc() != flow) {
        cout << "Impossible" << endl;
    } else {
        const auto &graph = dinic.g_;
        vector<bool> used(N, false);
        vector<vector<int>> components;
        for(int i = 0; i < N; ++i) {
            if(used[i]) continue;
            int cur = i;
            used[i] = true;
            components.push_back(vector<int>());
            while(true) {
                components.back().push_back(cur+1);
                for(auto e : graph[cur]) {
                    if(e->flow != 0 && e->to < N && !used[e->to]) {
                        used[e->to] = true;
                        cur = e->to;
                        break;
                    }
                }
                if(cur+1 == components.back().back()) break;
            }
        }
        cout << components.size() << endl;
        for(const auto &c : components) {
            cout << c.size() << ' ';
            cout << c << endl;
        }
    }

    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
