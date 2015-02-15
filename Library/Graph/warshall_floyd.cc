// Warshall-Floyd algorithm.
// Calculates all-points-pair shortest distance.
//
// Runs in O(N^3).
template<typename T>
struct WarshallFloyd {
    vector<vector<Maybe<T>>> graph;
    int N;

    WarshallFloyd(int size) : graph(size), N(size) {
        for(auto &v : graph) {
            v.resize(size);
        }
    }

    void add_edge(int from, int to, const T &dist) {
        graph[from][to] = dist;
    }

    void freeze() {
        for(int k = 0; k < N; ++k) {
            for(int i = 0; i < N; ++i) {
                for(int j = 0; j < N; ++j) {
                    if(graph[i][k].valid && graph[k][j].valid) {
                        graph[i][j].update(graph[i][k] + graph[k][j]);
                    }
                }
            }
        }
    }

    const Maybe<T>& query(int from, int to) {
        return graph[from][to];
    }
};

// Used in:
// AOJ0144
