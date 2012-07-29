#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Tag {
    int to;
    string str;

    Tag() {}
    Tag(int to, const string &str) : to(to), str(str) {}
};

struct Queue_Tag {
    string str;
    int pos;

    Queue_Tag() {}
    Queue_Tag(const string &str, int pos) : str(str), pos(pos) {}

    bool operator < (const Queue_Tag &other) const {
        return str > other.str;
    }
};

int main() {
    while(true) {
        int N, A, S, G;
        cin >> N >> A >> S >> G;
        if(!N && !A && !S && !G) break;

        vector<vector<Tag> > v(N);
        for(int i = 0; i < A; ++i) {
            Tag t;
            int x;
            cin >> x >> t.to >> t.str;
            v[x].push_back(t);
        }

        vector<vector<string> > dp(N, vector<string>(6*2*N+1));
        vector<vector<int> > visited(N, vector<int>(6*2*N+1, 0));
        dp[S][0] = "";

        priority_queue<Queue_Tag> q;
        q.push(Queue_Tag("", S));
        while(!q.empty()) {
            const Queue_Tag qt = q.top();
            q.pop();

            if(visited[qt.pos][qt.str.size()]) continue;
            visited[qt.pos][qt.str.size()] = 1;
            dp[qt.pos][qt.str.size()] = qt.str;

            for(int i = 0; i < v[qt.pos].size(); ++i) {
                const Tag &t = v[qt.pos][i];
                const string next = qt.str + t.str;
                if(next.size() > 6*2*N) continue;
                if(visited[t.to][next.size()]) continue;
                q.push(Queue_Tag(next, t.to));
            }
        }

        string ans = "NO";
        bool loop = false;
        bool found = false;
        for(int i = 0; i <= 6*2*N; ++i) {
            if(visited[G][i]) {
                if(i >= 6*N && found && dp[G][i] < ans) loop = true;
                if(found) ans = min(ans, dp[G][i]);
                else ans = dp[G][i];
                //cout << ans << endl;
                found = true;
            }
        }

        if(loop) cout << "NO" << endl;
        else cout << ans << endl;
    }

    return 0;
}
