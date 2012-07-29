#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int dfs(const vector<vector<pair<int, int> > > &v, int idx, vector<int> &used, int needs) {
    int ans = 0;

    for(int i = idx; i < v.size(); ++i) {
        int used_cnt = 0;
        for(int j = 0; j < v[i].size(); ++j) {
            if(used[v[i][j].first]) {
                ++used_cnt;
            }
        }
        if(used_cnt != needs) continue;

        used[i] = 1;
        int score = 0;
        for(int k = 0; k < used.size(); ++k) {
            if(!used[k]) continue;
            int sat = 10000000;
            for(int l = 0; l < v[k].size(); ++l) {
                if(used[v[k][l].first]) sat = min(sat, v[k][l].second);
            }
            if(sat == 10000000) sat = 0;
            score += sat;
            //cout << k << ' ';
        }
        //cout << ':' << score << endl;
        ans = max(ans, score);
        ans = max(ans, dfs(v, i+1, used, needs+1));
        used[i] = 0;
    }

    return ans;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<pair<int, int> > > friends(N);
    for(int i = 0; i < M; ++i) {
        int u, v, f;
        cin >> u >> v >> f;
        --u; --v;
        friends[u].push_back(make_pair(v, f));
        friends[v].push_back(make_pair(u, f));
    }

    vector<int> tmp(N, 0);
    cout << dfs(friends, 0, tmp, 0) << endl;

    return 0;
}
