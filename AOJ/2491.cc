//Name: Sanpo
//Level: 4
//Category: グラフ,Graph,木,Tree,Euler tour technique,動的計画法,DP
//Note:

/**
 * Euler tour techniqueで木を1次元に潰す。
 *
 * 木の上で辺を1回たどると、根に戻ってくるためにはもう1回逆向きにたどる必要があるため、
 * どの辺もたどられる回数は偶数となることがわかる。
 * この制約を表現するため、木を下っていく辺では何もせず、上っていく辺で2倍のコストと価値を加算するようにする。
 *
 * このとき、1次元に潰された木の上で、使う時間に対する最大価値についてDPをする。
 * 下っていくときは辺のコストと価値は0なので、DP表は直前の状態と等しくなる。
 * 上っていくときは、
 * ・たどる辺より下のsubtreeを使わないとき、もっとも最近にその頂点を訪問したときのDP表の値を採用する。
 * ・たどる辺より下のsubtreeを使うとき、1往復分のコストと価値は必ず加算した上で、合計ceil(m/2)回まで往復できる。
 * 2番めのパターンは個数制限付きナップザック問題になるため、コストを2進展開してlog m個の荷物にすることで
 * O(T log m)で更新ができる。
 * m_iが奇数のとき、価値が辺1回分しかない荷物が発生することに注意。
 *
 * オーダーはO(NT log M)。
 * ここで、Mはmax(m_i)である。
 * また、以下の実装では1番目のパターンを手抜きしているため、O(N^2T log M)になっている。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;

struct Edge {
    int to, t, m;
    LL v;
};

void dfs(int v, int parent, const vector<vector<Edge>> &graph, vector<pair<int,Edge>> &ord) {
    for(const auto &e : graph[v]) {
        if(e.to == parent) continue;
        ord.push_back(make_pair(e.to, e));
        dfs(e.to, v, graph, ord);
        ord.push_back(make_pair(v, e));
    }
}

bool solve() {
    int N, T;
    if(!(cin >> N >> T)) return false;
    if(!N && !T) return false;

    vector<vector<Edge>> graph(N);
    for(int i = 0; i < N-1; ++i) {
        int a, b, t, m;
        LL v;
        cin >> a >> b >> t >> m >> v;
        --a; --b;
        graph[a].push_back((Edge){b, t, m, v});
        graph[b].push_back((Edge){a, t, m, v});
    }
    
    vector<pair<int,Edge>> ord;
    ord.push_back(make_pair(0, Edge()));
    dfs(0, -1, graph, ord);
    const int M = ord.size();
    vector<vector<LL>> dp(M, vector<LL>(T+1, -1));
    dp[0][0] = 0;
    for(int i = 1; i < M; ++i) {
        const int v = ord[i].first;
        const Edge &e = ord[i].second;
        if(v != e.to) { //back
            int rem = e.m;
            // should pay 2
            for(int t = T; t >= 0; --t) {
                if(t-e.t*2 >= 0 && dp[i-1][t-e.t*2] >= 0) dp[i][t] = dp[i-1][t-e.t*2] + min(2, e.m)*e.v;
            }
            rem -= min(2, e.m);
            // optionally pay 1 if e.m is odd
            if(rem % 2 == 1) {
                for(int t = T; t >= 0; --t) {
                    if(t-e.t*2 >= 0 && dp[i][t-e.t*2] >= 0) dp[i][t] = max(dp[i][t], dp[i][t-e.t*2] + e.v);
                }
                --rem;
            }
            // binary dp
            for(int k = 2; rem > 0; k *= 2) {
                const int s = min(k, rem);
                const int dt = e.t * s;
                const int dv = e.v * s;
                for(int t = T; t >= 0; --t) {
                    if(t-dt >= 0 && dp[i][t-dt] >= 0) dp[i][t] = max(dp[i][t], dp[i][t-dt] + dv);
                }
                rem -= s;
            }
        } else {
            dp[i] = dp[i-1];
        }
        // Ignore current subtree
        for(int j = i-1; j >= 0; --j) {
            if(ord[j].first == v) {
                for(int t = 0; t <= T; ++t) {
                    dp[i][t] = max(dp[i][t], dp[j][t]);
                }
                break;
            }
        }
        /*
        cout << i << ' ' << v << ": ";
        for(auto val : dp[i]) {
            cout << val << ' ';
        }
        cout << endl;
        */
    }
    cout << *max_element(dp[M-1].begin(), dp[M-1].end()) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
