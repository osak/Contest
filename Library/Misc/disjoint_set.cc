struct DisjointSet {
    vector<int> parent;

    DisjointSet(size_t s) : parent(s, -1) {}

    int root(int u) {
        if(parent[u] < 0) return u;
        return parent[u] = root(parent[u]);
    }

    bool unite(int u, int v) {
        const int ru = root(u);
        const int rv = root(v);
        if(ru == rv) return false;
        if(size(ru) > size(rv)) {
            parent[ru] += parent[rv];
            parent[rv] = ru;
        } else {
            parent[rv] += parent[ru];
            parent[ru] = rv;
        }
        return true;
    }

    int size(int u) {
        return -parent[root(u)];
    }
};
