#include <iostream>
#include <vector>

using namespace std;

struct Constraint {
    int l, r;
    int num;
};

vector<Constraint> constraints;
vector<int> ans;
int ans_sum = -1;
int N, X;

bool check(const vector<int> &v, const vector<int> &sum) {
    for(auto c : constraints) {
        const int cnt = sum[c.r] - sum[c.l] + v[c.l];
        if(cnt != c.num) return false;
    }
    return true;
}

void dfs(vector<int> &v, vector<int> &sum, int depth) {
    if(depth == N) {
        if(check(v, sum)) {
            if(sum[N-1] > ans_sum) {
                ans = v;
                ans_sum = sum[N-1];
            }
        }
        return;
    }

    for(int i = 0; i <= X; ++i) {
        v[depth] = i;
        sum[depth] = (depth > 0) ? sum[depth-1] : 0;
        sum[depth] += i;
        dfs(v, sum, depth+1);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int M;
    cin >> N >> X >> M;
    vector<int> v(N, 0), sum(N, 0);
    constraints.resize(M);
    for(int i = 0; i < M; ++i) {
        Constraint &c = constraints[i];
        cin >> c.l >> c.r >> c.num;
        --c.l; --c.r;
    }
    dfs(v, sum, 0);
    if(ans_sum != -1) {
        bool first = true;
        for(auto i : ans) {
            if(!first) cout << ' ';
            cout << i;
            first = false;
        }
        cout << endl;
    } else {
        cout << -1 << endl;
    }
    return 0;
}

