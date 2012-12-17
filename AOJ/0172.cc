//Name: Doctor's Research Rooms
//Level: 3
//Category: 探索
//Note:

/*
 * 現在地と各部屋の電気が点いているかどうかを状態に持って幅優先探索．
 * 自分がいる部屋の電気を消してはいけないことに注意．
 * また，経路復元のときにスイッチを操作する順番に制約がある．
 *
 * オーダーは O(N^2 2^N)．
 */
#define _GLIBCXX_DEBUG
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

struct Tag {
    int pos, state, cost;

    Tag() : pos(0), state(0), cost(0) {}
    Tag(int p, int s, int c) : pos(p), state(s), cost(c) {}

    bool operator <(const Tag &other) const {
        return cost > other.cost; // Reversed order
    }
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int N, M;
        cin >> N >> M;
        if(!N && !M) break;

        vector<vector<int> > graph(N, vector<int>(N, 0));
        vector<vector<int> > sw(N, vector<int>(N, 0));
        for(int i = 0; i < M; ++i) {
            int S, T;
            cin >> S >> T;
            graph[S-1][T-1] = graph[T-1][S-1] = 1;
        }
        Tag init;
        for(int i = 0; i < N; ++i) {
            int v;
            cin >> v;
            init.state |= (v<<i);
        }
        for(int i = 0; i < N; ++i) {
            int K;
            cin >> K;
            while(K--) {
                int n;
                cin >> n;
                sw[i][n-1] = 1;
            }
        }
        vector<vector<Tag> > prev(N, vector<Tag>(1<<N));
        vector<vector<int> > memo(N, vector<int>(1<<N, INT_MAX));
        memo[init.pos][init.state] = 0;
        queue<Tag> q;
        q.push(init);
        int ans1 = -1;
        int ans2 = -1;
        if((init.state & 1) == 0) goto end;
        while(!q.empty()) {
            Tag t = q.front();
            q.pop();

            if(memo[t.pos][t.state] < t.cost) continue;
            //cout << t.pos << ' ' << t.state << endl;
            if(t.pos == N-1) {
                if(t.state == (1<<(N-1))) {
                    ans1 = t.cost;
                    break;
                } else if(ans2 == -1) {
                    ans2 = t.cost;
                }
            }
            // Switch
            for(int i = 0; i < N; ++i) {
                if(i != t.pos && sw[t.pos][i]) {
                    Tag nt(t.pos, t.state ^ (1<<i), t.cost+1);
                    if(memo[nt.pos][nt.state] > nt.cost) {
                        prev[nt.pos][nt.state] = t;
                        memo[nt.pos][nt.state] = nt.cost;
                        q.push(nt);
                    }
                }
            }

            // Move
            for(int i = 0; i < N; ++i) {
                if(graph[t.pos][i] && (t.state & (1<<i))) {
                    Tag nt(i, t.state, t.cost+1);
                    if(memo[nt.pos][nt.state] > nt.cost) {
                        prev[nt.pos][nt.state] = t;
                        memo[nt.pos][nt.state] = nt.cost;
                        q.push(nt);
                    }
                }
            }
        }
end:
        if(ans1 == -1 && ans2 == -1) {
            cout << "Help me!" << endl;
        } else if(ans1 == -1 && ans2 != -1) {
            cout << "You can not switch off all lights." << endl;
        } else {
            vector<Tag> history;
            Tag t(N-1, 1<<(N-1), 0);
            while(t.pos != init.pos || t.state != init.state) {
                //cout << t.pos << ' ' << t.state << endl;
                history.push_back(t);
                t = prev[t.pos][t.state];
            }
            history.push_back(init);
            reverse(history.begin(), history.end());
            cout << "You can go home in " << ans1 << " steps." << endl;
            vector<pair<int,bool> > buf;
            for(int i = 0; i < ans1; ++i) {
                const Tag &cur = history[i];
                const Tag &next = history[i+1];
                if(cur.pos != next.pos) {
                    sort(buf.begin(), buf.end());
                    for(vector<pair<int,bool> >::iterator it = buf.begin(); it != buf.end(); ++it) {
                        cout << "Switch " << (it->second?"on":"off") << " room " << it->first+1 << "." << endl;
                    }
                    buf.clear();
                    cout << "Move to room " << next.pos+1 << "." << endl;
                } else {
                    int diff = cur.state ^ next.state;
                    bool on = (next.state & diff) != 0;
                    int pos = 0;
                    while(!(diff & (1<<pos))) ++pos;
                    buf.push_back(make_pair(pos, on));
                }
            }
            sort(buf.begin(), buf.end());
            for(vector<pair<int,bool> >::iterator it = buf.begin(); it != buf.end(); ++it) {
                cout << "Switch " << (it->second?"on":"off") << " room " << it->first+1 << "." << endl;
            }
        }
    }
    return 0;
}
