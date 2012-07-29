#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

//edmonds_carpのヘルパー
//Verified PKU 1459
bool find_augment_path(const vector<vector<int> > &capacity, const vector<vector<int> > &flow, vector<int> &augment_path, int S, int G) {
    int N = (int)capacity.size();
    queue<int> q;
    vector<int> prev(N, -1);
    q.push(S);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        if(u == G) {
            int pos = 0;
            int v = G;
            while(v != -1) {
                augment_path[pos++] = v;
                v = prev[v];
            }
            reverse(augment_path.begin(), augment_path.begin()+pos);
            return true;
        }
        //Sourceへは行かないようにする
        for(int i = 0; i < N; ++i) {
            if(i == S) continue;
            if(prev[i] != -1) continue;
            if(capacity[u][i] - flow[u][i] > 0) {
                prev[i] = u;
                q.push(i);
            }
        }
    }
    return false;
}

//Verified PKU 1459
//ノード[S]がSource, [G]がTerminal
void edmonds_carp(const vector<vector<int> > &capacity, vector<vector<int> > &flow, int S, int G) {
    int N = (int)capacity.size();
    vector<int> augment_path(N, -1);
    while(find_augment_path(capacity, flow, augment_path, S, G)) {
        int aug = INT_MAX;
        for(int i = 0; augment_path[i] != G; ++i)
            aug = min(aug, capacity[augment_path[i]][augment_path[i+1]] - flow[augment_path[i]][augment_path[i+1]]);
        for(int i = 0; augment_path[i] != G; ++i) {
            int u = augment_path[i], v = augment_path[i+1];
            flow[u][v] += aug;
            flow[v][u] = -flow[u][v];
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int> > capacity(N+1, vector<int>(N+1, 0)), capacity_idx(N+1, vector<int>(N+1, 0));
    for(int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        capacity[a][b] = capacity[b][a] = 1;
        capacity_idx[a][b] = i+1;
    }

    int S, G;
    cin >> S >> G;
    vector<vector<int> > flow(N+1, vector<int>(N+1, 0));
    edmonds_carp(capacity, flow, S, G);

    int cap = 0;
    for(int i = 1; i <= N; ++i) {
        if(flow[i][G] != 0) cap += flow[i][G];
    }

    vector<int> changes;
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            if(flow[i][j] > 0) {
                if(!capacity_idx[i][j]) changes.push_back(capacity_idx[j][i]);
            }
        }
    }

    cout << cap << endl;
    cout << changes.size() << endl;
    for(int i = 0; i < changes.size(); ++i) {
        cout << changes[i] << endl;
    }

    return 0;
}
