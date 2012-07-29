#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace std;

int get(char c, const vector<int> &m, const vector<int> &v) {
    return v[m[c-'A']];
}

int dfs(vector<string> &strs, const vector<vector<pair<int, int> > > &m, int pos, vector<int> &used) {
    if(pos == m.size()) {
        int sum = 0;
        for(int i = 0; i < strs.size()-1; ++i) {
        //    cout << strs[i] << endl;
            sum += atoi(strs[i].c_str());
        }
        //cout << atoi(strs.back().c_str()) << endl;
        if(sum == atoi(strs.back().c_str())) return 1;
        return 0;
    }

    int cnt = 0;
    for(int i = 0; i < 10; ++i) {
        if(used[i]) continue;
        used[i] = 1;
        bool valid = true;
        for(int j = 0; j < m[pos].size(); ++j) {
            pair<int,int> p = m[pos][j];
            if(i == 0 && p.second == 0 && strs[p.first].size() > 1) {
                valid = false;
                break;
            }
            strs[p.first][p.second] = i + '0';
        }
        if(valid) cnt += dfs(strs, m, pos+1, used);
        used[i] = 0;
    }
    return cnt;
}


int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<int> mi(26, -1);
        vector<string> v(N);
        int seq = 0;
        for(int i = 0; i < N; ++i) {
            cin >> v[i];
            for(int j = 0; j < v[i].size(); ++j) {
                char c = v[i][j];
                if(mi[c-'A'] == -1) mi[c-'A'] = seq++;
            }
        }

        vector<vector<pair<int, int> > > m(seq);
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < v[i].size(); ++j) {
                int chi = mi[v[i][j]-'A'];
                m[chi].push_back(make_pair(i, j));
            }
        }

        vector<int> used(10, 0);
        cout << dfs(v, m, 0, used) << endl;
    }

    return 0;
}
