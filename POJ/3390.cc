//Name: Print Words in Lines
//Level: 3
//Category: グラフ,Graph,ダイクストラ,Dijkstra
//Note:

/*
 * 状態は「単語をどこまで使ったか」と「今何文字目にいるか」なので
 * これらの状態に到達するためのコストを記録してダイクストラ．
 * 1つの状態からは改行するか否かの遷移しかないため，辺は全ノードで2本しか出ない．
 *
 * オーダーは O(NM log NM)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

struct Tag {
    int idx, pos;
    int cost;

    Tag(int idx, int pos, int cost) : idx(idx), pos(pos), cost(cost) {}

    bool operator <(const Tag &other) const {
        return cost > other.cost; // Reverse order
    }
};

inline int pow2(int i) {
    return i*i;
}

const int INF = INT_MAX;
int memo[10000][100];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int C;
    cin >> C;
    while(C--) {
        int M, N;
        cin >> M >> N;
        vector<int> v(N);
        for(int i = 0; i < N; ++i) cin >> v[i];

        int ans = INT_MAX;
        fill_n((int*)memo, sizeof(memo)/sizeof(int), INT_MAX);
        priority_queue<Tag> q;
        q.push(Tag(-1, 0, 0));
        while(!q.empty()) {
            Tag t = q.top();
            q.pop();

            if(t.idx+1 == N) {
                int cost = t.cost + pow2(M-t.pos);
                ans = min(ans, cost);
                continue;
            }
            if(t.idx >= 0 && memo[t.idx][t.pos] < t.cost) continue;

            // append
            {
                int npos = t.pos + v[t.idx+1];
                if(t.pos > 0) ++npos;
                if(npos <= M && memo[t.idx+1][npos] > t.cost) {
                    memo[t.idx+1][npos] = t.cost;
                    q.push(Tag(t.idx+1, npos, t.cost));
                }
            }
            // Newline
            {
                int npos = 0 + v[t.idx+1];
                int ncost = t.cost + pow2(M-t.pos);
                if(memo[t.idx+1][npos] > ncost) {
                    memo[t.idx+1][npos] = ncost;
                    q.push(Tag(t.idx+1, npos, ncost));
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
