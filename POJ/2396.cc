//Name: Budget
//Level: 3
//Category: 最大流,Maximum Flow,Special Judge
//Note:

/*
 * 線型計画問題のように見えるが，制約が方程式ではなく個々の変数についてしか存在しないので最大流に落とせる．
 * 具体的には行に対応するノードと列に対応するノードをつくり，ソースから行に対応するノードそれぞれにrow_sum[i]，
 * 列に対応するノードからシンクにcol_cum[i]のキャパシティを与え，これらのノード間を適当な枝でつなげばよい．
 * 枝のキャパシティは制約条件を以下のように処理すれば得られる．
 * ・ < 条件のとき，キャパシティを指定された値まで減らす．
 * ・ > 条件のとき，ソースから対応する行の枝と列からシンクの枝でキャパシティを減らす．
 *   この値は別に取っておき，最後に合計する．
 * ・ = 条件のとき，< 条件と > 条件の両方の処理を行う．
 *   他の制約と矛盾しないように注意．
 * これで最大流を解き，フローと > 条件の伏流を加えて答となる．
 * 各所で制約条件に矛盾していないか確認するのを忘れないこと．
 *
 * オーダーはDinicが O(V^2 E)．
 * ここで V = R+C, E = O(R*C)．
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
#include <numeric>

using namespace std;

const int INF = 1000000000;

template <class T>
T dinic_augment(const vector<vector<T> > &capacity, int N, vector<vector<T> > &flow, vector<int> &level, vector<int> &finished, int u, int sink, T cur)/*{{{*/
{
    if (u == sink || cur == 0) {
        return cur;
    }
    if (finished[u]) {
        return 0;
    }
    finished[u] = true;
    for (int v = 0; v < N; v++) {
        if (capacity[u][v] - flow[u][v] > 0 && level[v] > level[u]) {
            const T f = dinic_augment(capacity, N, flow, level, finished, v, sink, min(cur, capacity[u][v] - flow[u][v]));
            if (f > 0) {
                flow[u][v] += f;
                flow[v][u] -= f;
                finished[u] = false;
                return f;
            }
        }
    }
    return 0;
}/*}}}*/

// O(V^2 E)
template <typename T>
T dinic(const vector<vector<T> > &capacity, vector<vector<T> > &flow, int N, int source, int sink)/*{{{*/
{
    //vector<vector<T> > flow(N, vector<T>(N, 0));
    T max_flow = 0;

    while (true) {
        vector<int> level(N, -1);
        level[source] = 0;
        queue<int> q;
        q.push(source);

        int d = N;
        while (!q.empty() && level[q.front()] < d) {
            const int u = q.front();
            q.pop();

            if (u == sink) {
                d = level[u];
            }
            for (int v = 0; v < N; v++) {
                if (level[v] < 0 && capacity[u][v] - flow[u][v] > 0) {
                    q.push(v);
                    level[v] = level[u] + 1;
                }
            }
        }

        vector<int> finished(N, false);
        bool updated = false;
        while (true) {
            const T f = dinic_augment(capacity, N, flow, level, finished, source, sink, INF);
            if (f == 0) {
                break;
            }
            max_flow += f;
            updated = true;
        }

        if (!updated) {
            break;
        }
    }

    return max_flow;
}/*}}}*/

int impossible() {
    cout << "IMPOSSIBLE" << endl << endl;
    return 1;
}

int solve() {
    int R, C;
    cin >> R >> C;
    vector<int> row_sum(R), col_sum(C);
    for(int i = 0; i < R; ++i) {
        cin >> row_sum[i];
    }
    for(int i = 0; i < C; ++i) {
        cin >> col_sum[i];
    }
    vector<vector<int> > base_num(R, vector<int>(C, 0));
    vector<vector<int> > max_num(R, vector<int>(C, INT_MAX));
    vector<vector<int> > equal_constraint(R, vector<int>(C, -1));
    int M;
    cin >> M;
    while(M--) {
        int r_, c_, v;
        char op;
        cin >> r_ >> c_ >> op >> v;
        const pair<int,int> r_range = r_ > 0 ? make_pair(r_-1, r_-1) : make_pair(0, R-1);
        const pair<int,int> c_range = c_ > 0 ? make_pair(c_-1, c_-1) : make_pair(0, C-1);
        for(int r = r_range.first; r <= r_range.second; ++r) {
            for(int c = c_range.first; c <= c_range.second; ++c) {
                if(op == '>') {
                    base_num[r][c] = max(base_num[r][c], v+1);
                } else if(op == '<') {
                    max_num[r][c] = min(max_num[r][c], v-1);
                } else if(op == '=') {
                    base_num[r][c] = max(base_num[r][c], v);
                    max_num[r][c] = min(max_num[r][c], v);
                    equal_constraint[r][c] = v;
                }
            }
        }
    }
    // Check consistency of equal constraint
    for(int r = 0; r < R; ++r) {
        for(int c = 0; c < C; ++c) {
            const int v = equal_constraint[r][c];
            if(v != -1) {
                if(base_num[r][c] != v || max_num[r][c] != v) return impossible();
            }
        }
    }
    const int SRC = R+C;
    const int SINK = R+C+1;
    vector<vector<int> > capacity(R+C+2, vector<int>(R+C+2, 0));
    vector<vector<int> > flow(R+C+2, vector<int>(R+C+2, 0));
    for(int r = 0; r < R; ++r) {
        for(int c = 0; c < C; ++c) {
            int cap = max_num[r][c] - base_num[r][c];
            if(cap < 0) return impossible();
            capacity[r][R+c] = cap;
            row_sum[r] -= base_num[r][c];
            col_sum[c] -= base_num[r][c];
            if(row_sum[r] < 0) return impossible();
            if(col_sum[c] < 0) return impossible();
        }
    }
    if(accumulate(row_sum.begin(), row_sum.end(), 0) != accumulate(col_sum.begin(), col_sum.end(), 0)) {
        return impossible();
    }
    for(int i = 0; i < R; ++i) {
        capacity[SRC][i] = row_sum[i];
    }
    for(int i = 0; i < C; ++i) {
        capacity[R+i][SINK] = col_sum[i];
    }
    dinic(capacity, flow, R+C+2, SRC, SINK);
    for(int i = 0; i < R; ++i) {
        if(flow[SRC][i] != row_sum[i]) return impossible();
    }
    for(int i = 0; i < C; ++i) {
        if(flow[R+i][SINK] != col_sum[i]) return impossible();
    }
    vector<vector<int> > ans(R, vector<int>(C, 0));
    for(int r = 0; r < R; ++r) {
        for(int c = 0; c < C; ++c) {
            if(c != 0) cout << ' ';
            cout << flow[r][R+c] + base_num[r][c];
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int N;
    cin >> N;
    while(N--) {
        solve();
    }
    return 0;
}
