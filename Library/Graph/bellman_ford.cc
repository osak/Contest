// Bellman-ford
// Runs in O(VE)
template<typename T>
T bellman_ford(const vector<vector<Edge<T>>> &g, int src, int dst) {
    const size_t N = g.size();
    vector<T> dist(N, numeric_limits<T>::max());
    dist[src] = 0;
    bool updated;
    do {
        updated = false;
        for (auto &es : v) {
            for (auto &e : es) {
                dist[e.to] = min(dist[e.to], dist[e.from] + e.cost);
                updated = true;
            }
        }
    } while(updated);
    return dist[dst];
}
