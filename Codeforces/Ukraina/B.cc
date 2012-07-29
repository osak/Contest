#include <iostream>
#include <algorithm>
#include <vector>
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

typedef long long LL;

int main() {
    int N, M, Y0, Y1;
    cin >> N >> M >> Y0 >> Y1;
    vector<int> mice(N);
    vector<int> cheeses(M);
    for(int i = 0; i < N; ++i) cin >> mice[i];
    for(int i = 0; i < M; ++i) cin >> cheeses[i];
    sort(mice.begin(), mice.end());
    sort(cheeses.begin(), cheeses.end());

    vector<int> edges(N, 0);
    vector<int> roots(N+M), levels(N+M, 0);
    for(int i = 0; i < N+M; ++i) roots[i] = i;

    vector<vector<int> > v(N);
    for(int i = 0; i < N; ++i) {
        int p2 = lower_bound(cheeses.begin(), cheeses.end(), mice[i]) - cheeses.begin();
        int p1 = p2-1;
        int d1 = INT_MAX, d2 = INT_MAX;
        if(p2 < cheeses.size()) d2 = abs(mice[i]-cheeses[p2]);
        if(p1 >= 0) d1 = abs(mice[i]-cheeses[p1]);
        if(d1 <= d2) {
            unite(i, N+p1, roots, levels);
            edges[i]++;
        }
        if(d2 <= d1) {
            unite(i, N+p2, roots, levels);
            edges[i]++;
        }
    }
    for(int i = 0; i < N; ++i) 
        v[getroot(i, roots)].push_back(i);

    int ans = 0;
    for(int i = 0; i < N; ++i) {
        int k = 0;
        int n = v[i].size();
        for(int j = 0; j < n; ++j) {
            int mouse = v[i][j];
            if(edges[mouse] == 2) ++k;
        }
        ans += max(0, n-k-1);
    }

    cout << ans << endl;
    return 0;
}
