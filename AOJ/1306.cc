#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>
#include <cstdlib>

using namespace std;

struct Tag {
    int score, idx, has;

    Tag() {}
    Tag(int s, int i, int h) : score(s), idx(i), has(h) {}

    bool operator < (const Tag &other) const {
        return score > other.score;
    }
};

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<pair<int, int> > v;
        for(int i = 0; i < N; ++i) {
            int P, T;
            cin >> P >> T;
            v.push_back(make_pair(P, T));
        }

        int ans = INT_MAX;
        vector<vector<int> > dp(N, vector<int>(4, INT_MAX));
        vector<int> visited(N, 0);
        priority_queue<Tag> q;
        if(v[0].first <= v[0].second) q.push(Tag(v[0].first, 0, 1));

        while(!q.empty()) {
            Tag t = q.top();
            q.pop();

            if(t.idx == N-1) {
                ans = min(ans, t.score + v[t.idx].first);
                continue;
            }
            if(dp[t.idx][t.has] <= t.score) continue;
            dp[t.idx][t.has] = t.score;
            visited[t.idx] = 1;

            //Bring baloons home
            if(t.has > 0) {
                const int nt = v[t.idx].second + v[t.idx].first*(t.has+1) + v[t.idx+1].first;
                const int ns = t.score + v[t.idx].first + v[t.idx+1].first;
                if(nt <= v[t.idx+1].second && dp[t.idx+1][1] > ns) {
                    q.push(Tag(ns, t.idx+1, 1));
                }
            }

            //Go forward
            if(t.has < 3) {
                const int dist = abs(v[t.idx].first - v[t.idx+1].first);
                const int nt = v[t.idx].second + dist*(t.has+1);
                const int ns = t.score + dist;
                if(nt <= v[t.idx+1].second && dp[t.idx+1][t.has+1] > ns) {
                    q.push(Tag(ns, t.idx+1, t.has+1));
                }
            }
        }
        if(ans == INT_MAX) {
            int missed;
            for(int i = 0; i < N; ++i) {
                if(!visited[i]) {
                    missed = i+1;
                    break;
                }
            }
            cout << "NG " << missed << endl;
        }
        else {
            cout << "OK " << ans << endl;
        }
    }

    return 0;
}
