#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

const int INF = 20000*500;

struct Edge {
    int u, v, w;

    bool operator < (const Edge &other) const {
        return w < other.w;
    }
};

//Verified PKU 2524
int getroot(int i, vector<int> &roots) {
    if(roots[i] == i) return i;
    else return (roots[i] = getroot(roots[i], roots));
}

//Verified PKU 2524
bool unite(int i, int j, vector<int> &roots, vector<int> &levels) {
    i = getroot(i, roots);
    j = getroot(j, roots);
    if(i == j) return false;

    if(levels[i] < levels[j]) {
        roots[i] = j;
    }
    else {
        roots[j] = i;
        if(levels[i] == levels[j]) ++levels[i];
    }
    return true;
}

int dfs(const vector<vector<Edge> > &mst, vector<int> &visited, int from, int to) {
    if(from == to) return 0;
    int cost = INF;

    visited[from] = 1;
    const vector<Edge> &v = mst[from];
    for(int i = 0; i < v.size(); ++i) {
        const Edge &e = v[i];
        int next = e.u==from ? e.v : e.u;
        if(visited[next]) continue;
        cost = min(cost, max(e.w, dfs(mst, visited, next, to)));
    }
    visited[from] = 0;

    return cost;
}

int main() {
    int T;
    scanf("%d", &T);

    for(int CASE = 1; CASE <= T; ++CASE) {
        int N, M;
        scanf("%d %d", &N, &M);

        vector<Edge> edges;
        for(int i = 0; i < M; ++i) {
            Edge e;
            scanf("%d %d %d", &e.u, &e.v, &e.w);
            edges.push_back(e);
        }
        sort(edges.begin(), edges.end());

        vector<vector<Edge> > mst(N);
        vector<int> roots(N);
        vector<int> levels(N, 0);
        for(int i = 0; i < N; ++i) roots[i] = i;
        for(int i = 0; i < edges.size(); ++i) {
            const Edge &e = edges[i];
            if(getroot(e.u, roots) == getroot(e.v, roots)) continue;
            mst[e.u].push_back(e);
            mst[e.v].push_back(e);
            unite(e.u, e.v, roots, levels);
        }

        int goal;
        scanf("%d", &goal);

        printf("Case %d:\n", CASE);
        for(int from = 0; from < N; ++from) {
            if(getroot(goal, roots) != getroot(from, roots)) {
                puts("Impossible");
            }
            else {
                vector<int> visited(N, 0);
                printf("%d\n", dfs(mst, visited, from, goal));
            }
        }
    }

    return 0;
}
