//Name: Company Trip
//Level: 3
//Category: グラフ,Graph,DAG,最長パス
//Note:

/**
 * 上司関係はDAGとなり、部屋の個数の下限は最長パスに含まれるノード数と等しい。
 * また、この数だけ部屋を用意すれば、ある最長パス以外のパスに含まれるノードは最長パスのノードと
 * 同じ部屋に入れられるため、最小の部屋数は上記のノード数と等しくなる。
 * したがって、問題は、取り去った時に最長パス長を短くするような辺を列挙することと等価である。
 *
 * 基本的には最長パス上にある辺を取り除けばよいが、迂回路がある場合は取り除いても無意味である。
 * ここで、辺(a,b)を取り除いても迂回路がある場合、その迂回路は最長パスの端点からの距離がaと等しいノード、bと等しいノードをそれぞれ含む。
 * また、逆に、最長パスの端点から上記のノードに到達可能な場合、これは辺(a,b)を取り除いたときの迂回路として働く。
 *
 * したがって、取り除いた時に最長パスが短くなる辺は、両端点(a,b)について、最長パスの端点からこれらの頂点までの距離が等しいノードが
 * 存在しないような辺である。
 * 全ての最長パスの端点候補からこの操作を行い、その積集合が答えとなる。
 *
 * オーダーはO((N+M) log M)。
 */
#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include <map>
#include <algorithm>

using namespace std;

bool solve() {
    int N, M;
    if(!(cin >> N >> M)) return false;
    if(!N && !M) return false;

    vector<vector<int>> graph(N);
    vector<vector<int>> rev_graph(N);
    map<pair<int,int>,int> edge_dict;
    vector<int> degree(N, 0);
    for(int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        graph[b].push_back(a);
        rev_graph[a].push_back(b);
        ++degree[a];
        edge_dict[make_pair(b, a)] = i;
    }

    vector<int> dp(N, 0);
    vector<int> prev(N, -1);
    vector<bool> longest_path(N, false);
    for(int i = N-1; i >= 0; --i) {
        if(degree[i] > 0) continue;
        queue<int> q;
        q.push(i);
        while(!q.empty()) {
            const int cur = q.front();
            q.pop();
            for(int neigh : graph[cur]) {
                if(dp[neigh] < dp[cur]+1) {
                    dp[neigh] = dp[cur] + 1;
                    prev[neigh] = cur;
                }
                if(--degree[neigh] == 0) {
                    q.push(neigh);
                }
            }
        }
    }
    const int longest = *max_element(dp.begin(), dp.end());
    bitset<200010> res;
    res.set();
    for(int i = 0; i < N; ++i) {
        bitset<200010> tmp;
        if(dp[i] == longest) {
            vector<int> q[2];
            q[0].push_back(i);
            while(q[0].size() > 0) {
                q[1].clear();
                for(int cur : q[0]) {
                    for(int neigh : rev_graph[cur]) {
                        if(dp[neigh] == dp[cur] - 1) {
                            q[1].push_back(neigh);
                        }
                    }
                }
                sort(q[1].begin(), q[1].end());
                q[1].erase(unique(q[1].begin(), q[1].end()), q[1].end());
                if(q[0].size() == 1 && q[1].size() == 1) {
                    tmp[edge_dict[make_pair(q[1][0], q[0][0])]] = true;
                }
                q[0].swap(q[1]);
            }
            res &= tmp;
        }
    }
    if(res.none()) {
        cout << -1 << endl;
    } else {
        for(int i = 0; i < M; ++i) {
            if(res[i]) cout << i+1 << endl;
        }
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
