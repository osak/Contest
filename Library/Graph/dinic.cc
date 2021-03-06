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
// Used in:
// AOJ2168, SPOJ(FASTFLOW), Codeforces 512C
