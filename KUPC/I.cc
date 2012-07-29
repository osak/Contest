#include <iostream>
#include <vector>

using namespace std;

struct Answer {
    vector<int> history1, history2;
};

bool check(int start, const vector<vector<int> > &dag, const vector<int> &used_, Answer &ans) {
    int pos = start;

    vector<int> used = used_;
    used[end] = false;

    ans.history2.clear();
    ans.history2.push_back(start);
    while(pos != end) {
        for(int i = 0; i < dag[pos].size(); ++i) {
            if(!used[i] && dag[pos][i]) {
                pos = i;
                used[pos] = true;
                break;
            }
        }
        ans.history2.push_back(pos);
    }
    for(int i = 0; i < used.size(); ++i)
        if(!used[i]) return false;

    return true;
}

bool dfs(int pos, const vector<vector<int> > &dag, vector<int> &used, Answer &ans) {
    used[pos] = true;
    ans.history1.push_back(pos);

    for(int i = 0; i < dag[pos].size(); ++i) {
        if(used[i]) continue;
        if(dfs(i, dag, used, ans)) {
            if(check(ans.history1[0], dag, used, ans)) return true;
        }
    }

    used[pos] = false;
    ans.history1.pop_back();

    return false;
}

int main() {
    ios::sync_with_stdio(0);

    int H, W;
    cin >> H >> W;

    vector<vector<int> > v(H, vector<int>(W));
    for(int r = 0; r < H; ++r) 
        for(int c = 0; c < W; ++c)
            cin >> v[r][c];

    vector<vector<int> > row_dag(H, vector<int>(H, 0));
    for(int r1 = 0; r1 < H; ++r1) {
        for(int r2 = 0; r2 < r1; ++r2) {
            bool gt = true, lt = true;
            for(int i = 0; i < W; ++i) {
                if(v[r1][i] <= v[r2][i]) gt = false;
                if(v[r1][i] >= v[r2][i]) lt = false;
            }
            if(gt) row_dag[r1][r2] = 1;
            if(lt) row_dag[r2][r1] = 1;
        }
    }
