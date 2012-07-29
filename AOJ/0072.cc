//Name: Carden Lantern
//Level: 2
//Category: 最小全域木,MST,グラフ,Graph
//Note:

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Road {
    int a, b;
    int dist;

    bool operator < (const Road &other) const {
        return dist < other.dist;
    }
};

int getroot(int i, vector<int> &roots) {
    if(roots[i] == i) return i;
    return roots[i] = getroot(roots[i], roots);
}

void unite(int i, int j, vector<int> &roots) {
    roots[getroot(i, roots)] = getroot(j, roots);
}

int main() {
    while(true) {
        int N, M;
        cin >> N;
        if(!N) break;
        cin >> M;

        vector<Road> roads(M);
        char comma;
        for(int i = 0; i < M; ++i) 
            cin >> roads[i].a >> comma >> roads[i].b >> comma >> roads[i].dist;
        sort(roads.begin(), roads.end());

        int ans = 0;
        vector<int> roots(N);
        for(int i = 0; i < N; ++i) roots[i] = i;
        for(int i = 0; i < M; ++i) {
            const Road &r = roads[i];
            if(getroot(r.a, roots) == getroot(r.b, roots)) continue;
            unite(r.a, r.b, roots);
            ans += r.dist/100 - 1;
        }
        cout << ans << endl;
    }
    return 0;
}
