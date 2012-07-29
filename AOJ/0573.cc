#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#include <map>
#include <ext/hash_map>

using namespace std;
using namespace __gnu_cxx;

struct Tag {
    int t, n, val;

    Tag() {}
    Tag(int t, int n, int val) : t(t), n(n), val(val) {}

    bool operator <(const Tag &other) const {
        return t > other.t;
    }
};

struct Cmp {
    size_t operator()(const pair<int,int> &p) const {
        return p.first*3001+p.second;
    }
};

int main() {
    ios::sync_with_stdio(0);

    int N, T, S;
    cin >> N >> T >> S;

    vector<pair<int,int> > xs(N);
    for(int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        xs[i] = make_pair(x, y);
    }

    int ans = 0;
    hash_map<pair<int,int>, int, Cmp> memo;
    priority_queue<Tag> q;
    q.push(Tag(0, 0, 0));
    while(!q.empty()) {
        Tag t = q.top();
        q.pop();

        pair<int,int> key = make_pair(t.t, t.n);
        if(memo.count(key) > 0) {
            if(memo[key] > t.val) continue;
        }
        //cout << t.t << ' ' << t.n << ' ' << t.val << endl;
        memo[key] = t.val;
        ans = max(ans, t.val);

        {
            int nt = t.t+1;
            pair<int,int> nk = make_pair(nt, t.n);
            if(nt <= T && memo[nk] < t.val) {
                memo[nk] = t.val;
                q.push(Tag(nt, t.n, t.val));
            }
        }
        for(int i = t.n; i < N; ++i) {
            int nv = t.val + xs[i].first;
            int nt = t.t + xs[i].second;
            pair<int,int> nk = make_pair(nt, i+1);
            if(nt > T) continue;
            if(t.t < S && nt > S) continue; //花火を見ないといけない
            if(memo[nk] >= nv) continue;

            memo[nk] = nv;
            q.push(Tag(nt, i+1, nv));
        }
    }

    cout << ans << endl;
    return 0;
}
