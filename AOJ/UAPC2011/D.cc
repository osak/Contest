#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int getroot(int a, vector<int> &roots) {
    if(roots[a] == a) return a;
    return roots[a] = getroot(roots[a], roots);
}

void unite(int a, int b, vector<int> &roots) {
    roots[getroot(a, roots)] = getroot(b, roots);
}

struct Tag {
    int a, b, cost;

    Tag() {}
    Tag(int a, int b, int cost) : a(a), b(b), cost(cost) {}

    bool operator < (const Tag &other) const {
        return cost > other.cost;
    }
};

int main() {
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;
        vector<Tag> edges(M);

        for(int i = 0; i < M; ++i) cin >> edges[i].a >> edges[i].b >> edges[i].cost;
        sort(edges.begin(), edges.end());

        vector<int> roots(N);
        int selected = 0;
        int cost = 0;
        for(int i = 0; i < N; ++i) roots[i] = i;
        for(int i = 0; i < M; ++i) {
            const Tag &t = edges[i];
            if(t.cost < 0) cost += t.cost;
            if(getroot(t.a, roots) == getroot(t.b, roots)) {
                continue;
            }
            if(selected == N-2) {
                if(t.cost > 0) cost += t.cost;
            }
            else {
                unite(t.a, t.b, roots);
                selected++;
            }
        }
        cout << cost << endl;
    }
    return 0;
}
