#include <iostream>
#include <vector>
#include <utility>
#include <climits>
#include <algorithm>

using namespace std;

bool operator < (const pair<int, int> &a, const pair<int, int> &b) {
    if(a.first != b.first) return a.first < b.first;
    return a.second < b.second;
}

int main() {
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<pair<int, int> > p;
        vector<vector<int> > v(N+1, vector<int>(N+1, INT_MAX/2));

        p.push_back(make_pair(1, 100));
        for(int i = 0; i < M; ++i) {
            int n, y;
            cin >> n >> y;
            p.push_back(make_pair(n, y));
        }

        int E;
        cin >> E;
        for(int i = 0; i < E; ++i) {
            int s, t, w;
            cin >> s >> t >> w;
            if(v[s][t] > w) v[s][t] = v[t][s] = w;
        }

        for(int i = 0; i < N+1; ++i) v[i][i] = 0;

        for(int k = 0; k < N+1; ++k) 
            for(int i = 0; i < N+1; ++i)
                for(int j = 0; j < N+1; ++j)
                    v[i][j] = v[j][i] = min(v[i][j], v[i][k]+v[k][j]);

        vector<pair<int, int> > l;
        for(int i = 1; i <= N; ++i) {
            int cost = 0;
            bool ok = true;
            for(int j = 0; j < p.size(); ++j) {
                if(v[i][p[j].first] == INT_MAX/2) {
                    ok = false;
                    break;
                }
                cost += v[i][p[j].first] * p[j].second;
            }
            if(ok) l.push_back(make_pair(cost, i));
        }
        sort(l.begin(), l.end());
        int mincost = l[0].first;

        for(int i = 0; i<l.size() && l[i].first==mincost; ++i) {
            if(i > 0) cout << ' ';
            cout << l[i].second;
        }
        cout << endl;
    }
    return 0;
}
