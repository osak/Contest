//Name: Brave Princess Revisited
//Level: 2
//Category: グラフ,Graph,最短経路,ダイクストラ法,Dijkstra
//Note:

/*
 * [今いるノード][所持金]を状態にして、刺客の人数について最短経路を求める。
 *
 * ダイクストラ法でオーダーは O(M log N)。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Road {
    int to, fee;
    int cost;

    Road() {}
    Road(int t, int f, int c) : to(t), fee(f), cost(c) {}
};

struct Tag {
    int node, money;
    int cost;

    Tag() {}
    Tag(int n, int m, int c) : node(n), money(m), cost(c) {}

    bool operator < (const Tag &other) const {
        return cost > other.cost; // Reverse order
    }
};

const int INF = 10000*100*10;

bool solve() {
    int N, M, L;
    cin >> N >> M >> L;
    if(!N && !M & !L) return false;

    vector<vector<Road> > roads(N);
    for(int _ = 0; _ < M; ++_) {
        int a, b, d, e;
        cin >> a >> b >> d >> e;
        --a; --b;
        roads[a].push_back(Road(b, d, e));
        roads[b].push_back(Road(a, d, e));
    }

    int ans = INF;
    priority_queue<Tag> q;
    vector<vector<int> > memo(N, vector<int>(L+1, INF));
    memo[0][L] = 0;
    q.push(Tag(0, L, 0));
    while(!q.empty()) {
        const Tag t = q.top();
        q.pop();
        if(memo[t.node][t.money] < t.cost) continue;
        if(t.node == N-1) {
            ans = t.cost;
            break;
        }

        const vector<Road> &v = roads[t.node];
        for(vector<Road>::const_iterator it = v.begin(); it != v.end(); ++it) {
            {
                // Use guard
                const int nm = t.money - it->fee;
                if(nm >= 0 && t.cost < memo[it->to][nm]) {
                    memo[it->to][nm] = t.cost;
                    q.push(Tag(it->to, nm, t.cost));
                }
            }
            {
                // Not use guard
                const int nc = t.cost + it->cost;
                if(nc < memo[it->to][t.money]) {
                    memo[it->to][t.money] = nc;
                    q.push(Tag(it->to, t.money, nc));
                }
            }
        }
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    for(int case_num = 1; solve(); ++case_num) ;
    return 0;
}
