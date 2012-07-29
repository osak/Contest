#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstdio>
#include <stack>

using namespace std;

int gcd(int m, int n) {
    if(m < n) return gcd(n, m);
    while(n != 0) {
        int tmp = m % n;
        m = n;
        n = tmp;
    }
    return m;
}

//flow_vは接続配列
//pairは<行き先, コスト>
int maxflow(const vector<vector<pair<int, int> > > &flow_v, int s, int g) {
    int size = flow_v.size();
    //隣接行列に変換
    //最初から隣接行列渡しならここはいらない
    /*****ただし、逆方向に負のコストが入っているかは要確認*****/
    vector<vector<int> > capacity(size, vector<int>(size, 0));
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < flow_v[i].size(); ++j) {
            int to = flow_v[i][j].first;
            int cost = flow_v[i][j].second;
            capacity[i][to] = cost;
        }
    }
    vector<vector<int> > flow(size, vector<int>(size, 0));

    int ans = 0;
    while(true) {
        //幅優先探索でaugument flowをみつける
        queue<int> q;
        vector<int> prev(size, -1);
        prev[s] = s;
        q.push(s);
        while(!q.empty()) {
            int n = q.front();
            q.pop();
            for(int i = 0; i < size; ++i) {
                if(capacity[n][i]-flow[n][i] <= 0) continue;
                if(prev[i] != -1) continue;
                prev[i] = n;
                q.push(i);
                if(i == g) goto endloop;
            }
        }
endloop:
        if(prev[g] == -1) break;
        int res = INT_MAX;
        for(int i = g; prev[i] != i; i = prev[i]) {
            res = min(res, capacity[prev[i]][i]-flow[prev[i]][i]);
        }
        for(int i = g; prev[i] != i; i = prev[i]) {
            flow[prev[i]][i] += res;
            flow[i][prev[i]] -= res;
        }
        ans += res;
    }
    return ans;
}

//・左からフローが流れてくるため、右から左へ行くのは既に存在しているフローの逆流のみ
//・よって、右から左へ行って、そこでtrueで止まることはあり得ない
//　（左頂点は右へのmatchToがあり、かつそちらへは進めないので必ずfalseになる）
//・このアルゴリズムでは、
//　n：左頂点
//　g[n][i]：右頂点
//　matchTo[g[n][i]]：左頂点or-1
//　が成立している
bool bm_helper(const vector<vector<int> > &g, vector<int> &matchTo, int n, vector<bool> &used) {
    if(n == -1) return true;

    for(int i = 0; i < g[n].size(); ++i) {
        if(used[g[n][i]]) continue;
        //どうせこの頂点に戻ってきてもaugment pathは見つかるわけないので復元しなくてよい
        used[g[n][i]] = true;
        if(bm_helper(g, matchTo, matchTo[g[n][i]], used)) {
            matchTo[n] = g[n][i];
            matchTo[g[n][i]] = n;
            return true;
        }
    }
    return false;
}

//gは接続配列（湧きだし、吸い込みはいらない）
//Lはマッチングの左側頂点の境界（L未満が左側）
int bipartiteMatch(const vector<vector<int> > &g, int L) {
    int size = g.size();
    vector<int> match(size, -1);
    //深さ優先でaugment pathを見つける
    //Ford Furlkersonのアルゴリズム。
    //一回の走査で必ずフローが1は増えるため、
    //左側を全てなめ尽くしたあとは解になっている
    int cnt = 0;
    for(int i = 0; i < L; ++i) {
        vector<bool> used(g.size(), false);
        if(bm_helper(g, match, i, used)) ++cnt; //augment pathが見つかる->フローが1増える
    }
    return cnt;
}

int main() {
    while(true) {
        int m, n;
        cin >> m >> n;
        if(!m && !n) break;

        vector<int> cards(m+n);
        //vector<vector<pair<int, int> > > graph(m+n+2);
        vector<vector<int> > graph(m+n);
        //For maxflow
        /*
        for(int i = 0; i < m; ++i) {
            //cin >> cards[i];
            scanf("%d", &cards[i]);
            graph[m+n].push_back(make_pair(i, 1)); //Start node
        }
        for(int i = m; i < m+n; ++i) {
            scanf("%d", &cards[i]);
            for(int j = 0; j < m; ++j) {
                if(gcd(cards[i], cards[j]) > 1) {
                    graph[j].push_back(make_pair(i, 1));
                }
            }
            graph[i].push_back(make_pair(m+n+1, 1)); //Goal node
        }
        cout << maxflow(graph, m+n, m+n+1) << endl;
        */
    
        //For bipartiteMatch
        for(int i = 0; i < m; ++i) {
            scanf("%d", &cards[i]);
        }
        for(int i = m; i < m+n; ++i) {
            scanf("%d", &cards[i]);
            for(int j = 0; j < m; ++j) {
                if(gcd(cards[i], cards[j]) > 1) {
                    graph[j].push_back(i);
                }
            }
        }
        cout << bipartiteMatch(graph, m) << endl;
    }
    return 0;
}
