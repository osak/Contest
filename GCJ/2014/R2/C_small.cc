#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

typedef long long LL;
const LL MOD = 1000000007;
const int INF = 100000000;

const int DR[] = {0, -1, 0, 1};
const int DC[] = {1, 0, -1, 0};

template<typename T>
struct Edge {
    int from, to;
    T capacity, flow;
    Edge *back;

    Edge() : from(0), to(0), capacity(0), flow(0), back(nullptr) {}
    Edge(int f, int t, T cap, Edge *b) : from(f), to(t), capacity(cap), flow(0), back(b) {}
};

template<typename T>
void add_edge(vector<vector<Edge<T>*>> &graph, int from, int to, T cap) {
    auto ea = new Edge<T>(from, to, cap, nullptr);
    auto eb = new Edge<T>(to, from, 0, ea);
    ea->back = eb;
    graph[from].push_back(ea);
    graph[to].push_back(eb);
}

template <class T>
T dinic_augment(vector<vector<Edge<T>*>> &graph, vector<int> &level, vector<bool> &finished, int u, int sink, T cur)/*{{{*/
{
    if (u == sink || cur == 0) {
        return cur;
    }
    if (finished[u]) {
        return 0;
    }
    finished[u] = true;
    for(auto e : graph[u]) {
        if(e->capacity - e->flow > 0 && level[e->to] > level[u]) {
            const T f = dinic_augment(graph, level, finished, e->to, sink, min(cur, e->capacity - e->flow));
            if (f > 0) {
                e->flow += f;
                e->back->flow -= f;
                finished[u] = false;
                return f;
            }
        }
    }
    return 0;
}/*}}}*/

// O(V^2 E)
template <typename T>
T dinic(vector<vector<Edge<T>*>> &graph, int source, int sink)/*{{{*/
{
    const int N = graph.size();
    T max_flow = 0;

    vector<int> level(N);
    vector<bool> finished(N);
    while (true) {
        fill(level.begin(), level.end(), -1);
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
            for(auto e : graph[u]) {
                if (level[e->to] < 0 && e->capacity - e->flow > 0) {
                    q.push(e->to);
                    level[e->to] = level[u] + 1;
                }
            }
        }

        fill(finished.begin(), finished.end(), false);
        bool updated = false;
        while (true) {
            const T f = dinic_augment<T>(graph, level, finished, source, sink, INF);
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


void solve(int CASE) {
    int H, W, B;
    cin >> W >> H >> B;
    vector<vector<int>> field(H, vector<int>(W, 1));
    for(int i = 0; i < B; ++i) {
        int x0, y0, x1, y1;
        cin >> x0 >> y0 >> x1 >> y1;
        for(int r = y0; r <= y1; ++r) {
            for(int c = x0; c <= x1; ++c) {
                field[r][c] = 0;
            }
        }
    }

    vector<vector<Edge<int>*>> graph(W*H*2 + 2);
    const int OUT_HEAD = W*H;
    const int SRC = W*H*2;
    const int SINK = SRC+1;
    for(int r = 0; r < H; ++r) {
        for(int c = 0; c < W; ++c) {
            if(field[r][c] == 0) continue;
            add_edge(graph, r*W+c, OUT_HEAD+r*W+c, 1);
            for(int dir = 0; dir < 4; ++dir) {
                const int nr = r + DR[dir];
                const int nc = c + DC[dir];
                if(nr < 0 || nr >= H || nc < 0 || nc >= W) continue;
                if(field[nr][nc] != 0) {
                    add_edge(graph, OUT_HEAD+r*W+c, nr*W+nc, 1);
                }
            }
        }
    }
    for(int c = 0; c < W; ++c) {
        if(field[0][c] != 0) {
            add_edge(graph, SRC, 0*W+c, 1);
        }
        if(field[H-1][c] != 0) {
            add_edge(graph, OUT_HEAD+(H-1)*W+c, SINK, 1);
        }
    }
    cout << "Case #" << CASE << ": " << dinic(graph, SRC, SINK) << endl;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    for(int CASE = 1; CASE <= N; ++CASE) {
        solve(CASE);
    }
    return 0;
}
