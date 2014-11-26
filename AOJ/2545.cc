//Name: Lion
//Level: 2
//Category: 全探索
//Note:

/**
 * 制約が小さいので、それぞれの檻に何頭のライオンがいるかを全探索し、条件に合うか試せば良い。
 * オーダーは O(MNX^N)。
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Constraint {
    int l, r, s;
};

int X;
int best_acc;
vector<int> best;
void dfs(int pos, const vector<Constraint> &cs, vector<int> &res, int acc) {
    if(pos == res.size()) {
        for(auto &c : cs) {
            int sum = 0;
            for(int i = c.l-1; i < c.r; ++i) {
                sum += res[i];
            }
            if(sum != c.s) return;
        }
        if(acc > best_acc) {
            best_acc = acc;
            best = res;
        }
    } else {
        if(acc + ((int)res.size() - pos) * X <= best_acc) return;
        for(int i = X; i >= 0; --i) {
            res[pos] = i;
            dfs(pos+1, cs, res, acc + i);
        }
    }
}

bool solve() {
    int N, M;
    if(!(cin >> N >> X >> M)) return false;

    vector<Constraint> constraints(M);
    for(int i = 0; i < M; ++i) {
        Constraint &c = constraints[i];
        cin >> c.l >> c.r >> c.s;
    }
    vector<int> res(N);
    best.clear();
    best.push_back(-1);
    best_acc = -1;
    dfs(0, constraints, res, 0);
    for(int i = 0; i < best.size(); ++i) {
        if(i != 0) cout << " ";
        cout << best[i];
    }
    cout << endl;
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
