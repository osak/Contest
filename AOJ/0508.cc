#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

vector<vector<int> > v;

int dfs(int pos, vector<bool> &visited) {
    int ans = 0;
    visited[pos] = true;
    for(int i = 0; i < v[pos].size(); ++i) {
        if(visited[v[pos][i]]) continue;
        ans = max(ans, dfs(v[pos][i], visited));
    }
    visited[pos] = false;
    return ans+1;
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        v.clear();
        v.resize(100);
        for(int i = 0; i < N; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            v[a].push_back(b);
            v[b].push_back(a);
        }
        int ans = 0;
        for(int i = 0; i < 100; ++i) {
            vector<bool> visited(100, false);
            ans = max(ans, dfs(i, visited));
        }
        cout << ans << endl;
    }
    return 0;
}
