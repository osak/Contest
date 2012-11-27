//Name: Paid Roads
//Level: 3
//Category: グラフ,Graph,ダイクストラ,Dijkstra
//Note:

/*
 * 現在位置と訪問済みノードのビットマスクを状態としてダイクストラ．
 * オーダーは O(2^N*M log N)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

#define FOREACH(var,v) for(__typeof(v.begin()) var = v.begin(); var != v.end(); ++var)

struct Road {
    int a, b, c;
    int p, r;
};

struct Tag {
    int pos, mask;
    int cost;

    Tag(int p, int m, int c) : pos(p), mask(m), cost(c) {}

    bool operator <(const Tag &other) const {
        return cost > other.cost; // Reverse order
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, M;
    while(cin >> N >> M) {
        vector<Road> roads;
        vector<vector<pair<int,int> > > mask_by_c(N);
        for(int i = 0; i < M; ++i) {
            Road r;
            cin >> r.a >> r.b >> r.c >> r.p >> r.r;
            --r.a; --r.b; --r.c;
            roads.push_back(r);
        }

        vector<vector<int> > memo(N, vector<int>(1<<M, INT_MAX));
        priority_queue<Tag> q;
        q.push(Tag(0, 1, 0));
        memo[0][1] = 0;
        int ans = -1;
        while(!q.empty()) {
            const Tag t = q.top();
            q.pop();
            if(memo[t.pos][t.mask] < t.cost) continue;
            //cout << t.pos << ' ' << t.mask << ' ' << t.cost << endl;
            if(t.pos == N-1) {
                ans = t.cost;
                break;
            }

            for(int i = 0; i < M; ++i) {
                const Road &road = roads[i];
                if(road.a == t.pos) {
                    int nc = t.cost;
                    if(t.mask & (1<<road.c)) {
                        nc += road.p;
                    } else {
                        nc += road.r;
                    }
                    const int nm = t.mask | (1<<road.b);
                    if(nc < memo[road.b][nm]) {
                        memo[road.b][nm] = nc;
                        q.push(Tag(road.b, nm, nc));
                    }
                }
            }
        }
        if(ans == -1) {
            cout << "impossible" << endl;
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}
