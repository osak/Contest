#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <climits>

using namespace std;

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


struct Road {
    int a, b, g, s;
    Road() {}
    Road(int a_, int b_, int g_, int s_) : a(a_), b(b_), g(g_), s(s_) {}

    bool operator < (const Road &other) const {
        return s < other.s;
    }
};

int main() {
    int N, M;
    cin >> N >> M;
    int G, S;
    cin >> G >> S;

    vector<Road> roads(M);
    vector<int> golds(M);
    for(int i = 0; i < M; ++i) {
        cin >> roads[i].a >> roads[i].b >> roads[i].g >> roads[i].s;
        roads[i].a--;
        roads[i].b--;
        golds[i] = roads[i].g;
    }
    sort(roads.begin(), roads.end());
    sort(golds.begin(), golds.end());
    golds.erase(unique(golds.begin(), golds.end()), golds.end());

    long long cmin = 0, cmax = (1LL<<61);

    while(cmin < cmax) {
        long long cost = (cmin+cmax)/2;
        int left = 0, right = golds.size();
        bool cok = false;
        while(left < right) {
            int center = (left+right)/2;
            int gold = golds[center];
            vector<int> roots(N);
            vector<int> levels(N, 0);
            for(int i = 0; i < N; ++i) roots[i] = i;

            long long silver = (cost - gold*G)/S;
            if(silver < 0) {
                left = center+1;
                continue;
            }

            for(int i = 0; i < M; ++i) {
                const Road &r = roads[i];
                if(getroot(r.a, roots) == getroot(r.b, roots)) continue;
                if(r.g > gold || r.s > silver) continue;
                unite(r.a, r.b, roots, levels);
            }
            bool ok = true;
            for(int i = 0; i < N; ++i) {
                if(getroot(0, roots) != getroot(i, roots)) {
                    ok = false;
                    break;
                }
            }
            if(ok) {
                cok = true;
                break;
            }
            else left = center+1;
        }
        if(cok) cmax = cost;
        else cmin = cost+1;
    }
    int ans = (cmin+cmax)/2;
    if(ans > (1LL<<50)) cout << -1 << endl;
    else cout << (cmin+cmax)/2 << endl;

    return 0;
}
