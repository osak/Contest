//Name: Ombrophobic Bovines
//Level: 3
//Category: グラフ,Graph,最大流,Maximum Flow
//Note:

/*
 * 最初にWarshal-Floyedをかけることで，各頂点間の最短距離が求められる．
 * これを使うと牛の移動をフローで表現することができる．
 * 具体的にはFarm1つにつき2ノードを用意し，片方は入力，片方は出力として
 * ソースから入力ノードの辺には最初にいる牛のぶんだけ容量を与え，出力からシンクの辺には
 * シェルターのキャパシティだけ容量を与える．
 * 入力・出力ノード間は，通行可能であれば無限の容量を与える．
 *
 * あとは時間で二分探索し，使用可能な辺を切り替えながら牛の数と同じだけのフローを流せるか確かめればよい．
 * ただしDinicでも O(V^2 E) と結構厳しいので，二分探索の範囲を実際に出てきた距離で量子化 (高々40000要素になる) することと
 * キャパシティ行列を毎回更新せず，Dinicの中で有効・無効を見るだけで済ませている．
 *
 * オーダーは前処理のWarshall-Floyedが O(F^3)，Dinic が O(F^2 E) = O(F^4) 程度．
 * これに二分探索が加わるため，全体では O(F^4 log F) 程度となる．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

const long long DIST_INF = 1LL<<60;
const int INF = 1<<29;

template <class T>
T dinic_augment(const vector<vector<T> > &capacity, int N, vector<vector<T> > &flow, vector<int> &level, vector<int> &finished, int u, int sink, T cur, const vector<vector<long long> > &dist, long long limit)/*{{{*/
{
    if (u == sink || cur == 0) {
        return cur;
    }
    if (finished[u]) {
        return 0;
    }
    finished[u] = true;
    for (int v = 0; v < N; v++) {
        if (dist[u][v] <= limit && capacity[u][v] - flow[u][v] > 0 && level[v] > level[u]) {
            const T f = dinic_augment(capacity, N, flow, level, finished, v, sink, min(cur, capacity[u][v] - flow[u][v]), dist, limit);
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
T dinic(const vector<vector<T> > &capacity, int N, int source, int sink, const vector<vector<long long> > &dist, long long limit)/*{{{*/
{
    vector<vector<T> > flow(N, vector<T>(N, 0));
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
                if (dist[u][v] <= limit && level[v] < 0 && capacity[u][v] - flow[u][v] > 0) {
                    q.push(v);
                    level[v] = level[u] + 1;
                }
            }
        }

        vector<int> finished(N, false);
        bool updated = false;
        while (true) {
            const T f = dinic_augment(capacity, N, flow, level, finished, source, sink, INF, dist, limit);
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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int F, P;
    cin >> F >> P;
    vector<pair<int,int> > farm(F);
    vector<vector<long long> > dist(F, vector<long long>(F, DIST_INF));
    int sum = 0;
    for(int i = 0; i < F; ++i) {
        cin >> farm[i].first >> farm[i].second;
        sum += farm[i].first;
        dist[i][i] = 0;
    }
    for(int i = 0; i < P; ++i) {
        int a, b;
        long long d;
        cin >> a >> b >> d;
        --a; --b;
        dist[a][b] = min(dist[a][b], d);
        dist[b][a] = min(dist[b][a], d);
    }
    for(int k = 0; k < F; ++k) 
        for(int i = 0; i < F; ++i) 
            for(int j = 0; j < F; ++j)
                dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
    set<long long> distance_set;
    for(int i = 0; i < F; ++i)
        for(int j = 0; j < F; ++j)
            if(dist[i][j] < DIST_INF) distance_set.insert(dist[i][j]);
    distance_set.insert(-1); //sentinel
    vector<long long> distance_list(distance_set.begin(), distance_set.end());

    // 0...F: from
    // F...2F: to
    // 2F: source
    // 2F+1: sink
    vector<vector<int> > capacity(F*2+2, vector<int>(F*2+2, 0));
    vector<vector<long long> > dc(F*2+2, vector<long long>(F*2+2));
    for(int i = 0; i < F; ++i) {
        capacity[2*F][i] = farm[i].first;
        capacity[F+i][2*F+1] = farm[i].second;
        dc[2*F][i] = 0;
        dc[F+i][2*F+1] = 0;
    }
    for(int i = 0; i < F; ++i) {
        for(int j = i; j < F; ++j) {
            if(dist[i][j] < DIST_INF) capacity[i][F+j] = capacity[j][F+i] = INF;
            else capacity[i][F+j] = capacity[j][F+i] = 0;
            dc[i][F+j] = dc[j][F+i] = dist[i][j];
        }
    }

    int left = 0, right = distance_list.size();
    while(left+1 < right) {
        const int center = (left+right) >> 1;
        const long long limit = distance_list[center]; //inclusive
        int flow = dinic(capacity, F*2+2, F*2, F*2+1, dc, limit);
        if(flow < sum) left = center;
        else right = center;
    }

    if(right == (int)distance_list.size()) cout << -1 << endl;
    else cout << distance_list[right] << endl;
    return 0;
}
