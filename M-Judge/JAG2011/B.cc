#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool dfs(const vector<vector<int> > &v, int pos, vector<int> &history, vector<int> &used) {
    int N = v[pos].size();
    history.push_back(pos);
    used[pos] = 1;
    for(int i = 0; i < N; ++i) {
        int pt = v[pos][i];
        if(used[pt]) {
            vector<int>::iterator idx = find(history.begin(), history.end(), pt);
            if(idx == history.end()) continue;
            int sz = history.end()-idx;
            if(sz % 2 == 1) return true;
        }
        else if(dfs(v, pt, history, used)) return true;
    }
    history.pop_back();

    return false;
}

int main() {
    int V, E;
    cin >> V >> E;
    vector<vector<int> > v(V);
    for(int i = 0; i < E; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    vector<int> used(V, 0);
    vector<int> history;
    bool ok = true;
    for(int i = 0; i < V; ++i) {
        if(used[i]) continue;
        if(dfs(v, i, history, used)) {
            ok = false;
            break;
        }
    }
    if(!ok) cout << -1 << endl;
    else cout << V*(V-1)/2-V-E << endl;

    return 0;
}
