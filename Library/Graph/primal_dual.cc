// So-called Primal-Dual algorithm
// Solve minimum cost flow problem.
// O(VE(F + C))
template<typename Flow, typename Cost>
struct PrimalDual {
    struct Edge {
        int from, to;
        Flow cap, flow;
        Cost cost;
        Edge *back;
        Edge(int from, int to, Flow cap, Cost c, Edge *b) : from(from), to(to), cap(cap), flow(static_cast<Flow>(0)), cost(c), back(b) {}

        bool remain() const {
            return flow < cap;
        }

        Cost add_flow(Flow f) {
            flow += f;
            back->flow -= f;
            return cost * f;
        }
    };

    PrimalDual(int N, int src, int sink) : g_(N), N_(N), src_(src), sink_(sink) {}
    ~PrimalDual() {
        for(auto &es : g_) {
            for(auto &e : es) {
                delete e;
            }
        }
    }

    void add_edge(int from, int to, Flow cap, Cost cost) {
        Edge *e = new Edge(from, to, cap, cost, nullptr);
        Edge *r = new Edge(to, from, static_cast<Flow>(0), -cost, e);
        e->back = r;
        g_[from].push_back(e);
        g_[to].push_back(r);
    }

    pair<Flow,Cost> calc(Flow f) {
        pair<Flow,Cost> res;

        vector<Maybe<Cost>> memo(N_);
        vector<Edge*> prev(N_);
        while(static_cast<Flow>(0) < f) {
            for(auto &m : memo) {
                m.valid = false;
            }

            // Bellman-ford algorithm
            memo[src_] = static_cast<Cost>(0);
            bool updated = false;
            do {
                updated = false;
                for(int i = 0; i < N_; ++i) {
                    if(!memo[i].valid) continue;
                    for(const auto &e : g_[i]) {
                        if(e->remain()) {
                            if(memo[e->to].update(memo[e->from] + e->cost)) {
                                updated = true;
                                prev[e->to] = e;
                            }
                        }
                    }
                }
            } while(updated);

            if(!memo[sink_].valid) {
                break;
            }
            Flow reside = min(f, prev[sink_]->cap - prev[sink_]->flow);
            int cur = sink_;
            while(cur != src_) {
                reside = min(reside, prev[cur]->cap - prev[cur]->flow);
                cur = prev[cur]->from;
            }
            cur = sink_;
            while(cur != src_) {
                res.second += prev[cur]->add_flow(reside);
                cur = prev[cur]->from;
            }
            res.first += reside;
            f -= reside;
        }
        return res;
    }

private:
    vector<vector<Edge*>> g_;
    int N_, src_, sink_;
};

// Not Tested
