#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
typedef int LL;

struct Tag {
    int line, pos;
    LL cost;
    int transfer;

    Tag() : cost(0), transfer(0) {}
    Tag(int l, int p, LL c, int t) : line(l), pos(p), cost(c), transfer(t) {}

    bool operator < (const Tag &other) const {
        if(cost != other.cost) return cost > other.cost;
        return transfer > other.transfer;
    }
};

int main() {
    int N, T;
    cin >> N >> T;
    string A, B;
    cin >> A >> B;

    vector<vector<string> > line(N);
    vector<vector<int> > cost(N);
    map<string, vector<pair<int, int> > > transfer;
    map<pair<int,int>, int> dict;
    int seq = 1;

    for(int i = 0; i < N; ++i) {
        int Ai;
        cin >> Ai;
        for(int j = 0; j < Ai; ++j) {
            string station;
            cin >> station;
            line[i].push_back(station);
            transfer[station].push_back(make_pair(i, j));
            dict[make_pair(i,j)] = seq++;
        }
        for(int j = 0; j < Ai-1; ++j) {
            int c;
            cin >> c;
            cost[i].push_back(c);
        }
    }

    priority_queue<Tag> q;
    vector<pair<LL,int> > dp(100001, make_pair(1<<30, 100000));
    {
        const vector<pair<int,int> > &v = transfer[A];
        for(int i = 0; i < v.size(); ++i) {
            q.push(Tag(v[i].first, v[i].second, 0, 0));
        }
    }
    Tag ans = Tag(0, 0, -1, 0);
    while(!q.empty()) {
        Tag tag = q.top();
        q.pop();

        if(line[tag.line][tag.pos] == B) {
            ans = tag;
            while(!q.empty() && q.top().cost == ans.cost) {
                if(q.top().transfer < ans.transfer) ans = q.top();
                q.pop();
            }
            break;
        }
        int idx = dict[make_pair(tag.line, tag.pos)];
        if(dp[idx].first < tag.cost) continue;
        if(dp[idx].first == tag.cost && dp[idx].second <= tag.transfer) continue;
        dp[idx] = make_pair(tag.cost, tag.transfer);

        if(line[tag.line].size() > tag.pos+1) {
            LL nc = tag.cost + cost[tag.line][tag.pos];
            int st = dict[make_pair(tag.line, tag.pos+1)];
            if(dp[st].first > nc || (dp[st].first == nc && dp[st].second > tag.transfer)) {
                q.push(Tag(tag.line, tag.pos+1, nc, tag.transfer));
            }
        }
        if(tag.pos-1 >= 0) {
            LL nc = tag.cost + cost[tag.line][tag.pos-1];
            int st = dict[make_pair(tag.line, tag.pos-1)];
            if(dp[st].first > nc || (dp[st].first == nc && dp[st].second > tag.transfer)) {
                q.push(Tag(tag.line, tag.pos-1, nc, tag.transfer));
            }
        }

        const vector<pair<int,int> > &v = transfer[line[tag.line][tag.pos]];
        int SZ = v.size();
        for(int i = 0; i < SZ; ++i) {
            const pair<int,int> &tr = v[i];
            LL nc = tag.cost + T;
            int nt = tag.transfer + 1;
            int st = dict[make_pair(tr.first, tr.second)];
            if( dp[st].first > nc || (dp[st].first == nc && dp[st].second > nt)) {
                q.push(Tag(tr.first, tr.second, nc, nt));
            }
        }
    }

    if(ans.cost == -1) cout << -1 << endl;
    else cout << ans.cost << ' ' << ans.transfer << endl;

    return 0;
}
