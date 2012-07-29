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

    vector<vector<int> > v(M);
    for(int i = 0; i < N; ++i) {
        int p2 = lower_bound(cheeses.begin(), cheeses.end(), mice[i]) - cheeses.begin();
        int p1 = p2-1;
        int d1 = INT_MAX, d2 = INT_MAX;
        if(p2 < cheeses.size()) d2 = abs(mice[i]-cheeses[p2]);
        if(p1 >= 0) d1 = abs(mice[i]-cheeses[p1]);
        if(d1 <= d2) {
            v[p1].push_back(i);
            edges[i]++;
        }
        if(d2 <= d1) {
            v[p2].push_back(i);
            edges[i]++;
        }
    }
    
    vector<int> used(N, 0);
    for(int i = 0; i < M; ++i) {
        int minval1 = INT_MAX, minval2 = INT_MAX;
        int cx = cheeses[i];
        for(int j = 0; j < v[i].size(); ++j) {
            if(used[v[i][j]]) continue;
            int midx = v[i][j];
            int mx = mice[midx];
            if(edges[midx] == 1) minval1 = min(minval1, abs(cx-mx));
            if(edges[midx] == 2) minval2 = min(minval2, abs(cx-mx));
        }
        if(minval1 <= minval2) {
            for(int j = 0; j < v[i].size(); ++j) {
                int midx = v[i][j];
                int mx = mice[midx];
                if(edges[midx] == 1 && abs(cx-mx) == minval1) used[midx] = 1;
                if(edges[midx] == 2) edges[midx]--;
            }
        }
        else {
            int c1 = 0, c2 = 0;
            for(int j = 0; j < v[i].size(); ++j) {
                int midx = v[i][j];
                int mx = mice[midx];
                if(edges[midx] == 1 && abs(cx-mx) == minval1) c1++;
                if(edges[midx] == 2 && abs(cx-mx) == minval2) c2++;
            }
            if(c1 == 2) {
                for(int j = 0; j < v[i].size(); ++j) {
                    int midx = v[i][j];
                    int mx = mice[midx];
                    if(edges[midx] == 1 && abs(cx-mx) == minval1) used[midx] = 1;
                    if(edges[midx] == 2) edges[midx]--;
                }
            }
            else {
                for(int j = 0; j < v[i].size(); ++j) {
                    int midx = v[i][j];
                    int mx = mice[midx];
                    if(edges[midx] == 2) used[midx] = 1;
                }
            }
        }
    }

    int cnt = 0;
    for(int i = 0; i < N; ++i)
        if(!used[i]) ++cnt;
    cout << cnt << endl;

    return 0;
}
