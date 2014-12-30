//Name: Luigi's Tavern
//Level: 3
//Category: グラフ,Graph,最大流
//Note: 

/**
 * Hero, Warrior, Cleric, Mageの順に結んだ四部グラフを作り、最大流を求める。
 * Warrior, Cleric, Mageには、メンバーに対応する頂点のほか、利用しないという選択に対応する頂点も用意する。
 * このとき、ClericがWarriorとMageの間にいることによって、ClericがいないときにはWarriorとMageを入れなければならないという条件が自然に満たせる。
 *
 * 制約は「AとBが同じパーティのときには辺が張られていないといけない」であり、Bを選んでも必ずしもAがいなくてよい点に注意。
 *
 * オーダーは O(V^2 E)。
 * ただしこれはDinicのオーダーであり、実際はかなり高速に動く。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

template<typename T, T INF>
struct Dinic {
    struct Edge {
        int to;
        T cap, flow;
        Edge *back;
        Edge(int to, T cap, T flow, Edge *back) : to(to), cap(cap), flow(flow), back(back) {}

        bool remain() const {
            return flow < cap;
        }

        void add_flow(T f) {
            flow += f;
            back->flow -= f;
        }
    };

    vector<vector<Edge*>> g_;
    vector<int> memo_, level_;
    int src_, sink_;

    Dinic(int N, int src, int sink) : g_(N), memo_(N), level_(N), src_(src), sink_(sink) {}
    ~Dinic() {
        for (auto &row : g_) {
            for (auto e : row) {
                delete e;
            }
        }
    }

private:
    T dinic_augment(int v, T cap) {
        if(v == sink_) return cap;

        const int N = g_[v].size();
        for(int i = memo_[v]; i < N; ++i) {
            const auto &e = g_[v][i];
            if(level_[e->to] != level_[v]+1) continue;
            if(!e->remain()) continue;
            const T f = dinic_augment(e->to, min(cap, e->cap - e->flow));
            if(f > 0) {
                e->add_flow(f);
                return f;
            }
        }
        return 0;
    }

public:
    void add_edge(int from, int to, T cap) {
        //cout << from << ' ' << to << endl;
        Edge *e = new Edge(to, cap, 0, nullptr);
        Edge *r = new Edge(from, 0, 0, e);
        e->back = r;
        g_[from].push_back(e);
        g_[to].push_back(r);
    }

    T dinic() {
        T flow = 0;
        while(true) {
            // Calculate depth of each vertex
            fill(begin(level_), end(level_), -1);
            queue<int> q;
            q.push(src_);
            level_[src_] = 0;
            while(!q.empty()) {
                const int v = q.front();
                q.pop();
                for (const auto &e : g_[v]) {
                    if(e->remain() && level_[e->to] == -1) {
                        level_[e->to] = level_[v] + 1;
                        q.push(e->to);
                    }
                }
            }

            // Search for the residual path of shortest length
            bool updated = false;
            fill(begin(memo_), end(memo_), 0);
            while(true) {
                T add = dinic_augment(src_, INF);
                if(add == 0) break;
                flow += add;
                updated = true;
            }
            if(!updated) break;
        }
        return flow;
    }
};

bool solve(bool first) {
    int H, W, C, M, Nw, Nc, Nm;
    if(!(cin >> H >> W >> C >> M >> Nw >> Nc >> Nm)) return false;
    if(H < 0 && W < 0 && C < 0 && M < 0 && Nw < 0 && Nc < 0 && Nm < 0) return false;

    const int N = 1+H+W*2+2+C*2+2+M*2+2+1;
    const int WBASE = H;
    const int CBASE = WBASE + W*2 + 2;
    const int MBASE = CBASE + C*2 + 2;
    const int SRC = MBASE + M*2 + 2;
    const int SINK = SRC + 1;
    assert(SINK == N-1);

    Dinic<int, 100000> g(N, SRC, SINK);
    for(int i = 0; i < H; ++i) {
        g.add_edge(SRC, i, 1);
        g.add_edge(i, WBASE+W*2, 1);
    }

    for(int i = WBASE; i < WBASE+W*2; i += 2) {
        int k;
        cin >> k;
        while(k--) {
            int h;
            cin >> h;
            --h;
            g.add_edge(h, i, 1);
        }
        g.add_edge(i, i+1, 1);
        g.add_edge(i+1, CBASE+C*2, 1);
    }
    g.add_edge(WBASE+W*2, WBASE+W*2+1, Nw);

    for(int i = CBASE; i < CBASE+C*2; i += 2) {
        int k;
        cin >> k;
        while(k--) {
            int w;
            cin >> w;
            --w;
            g.add_edge(WBASE+w*2+1, i, 1);
        }
        g.add_edge(i, i+1, 1);
        g.add_edge(i+1, MBASE+M*2, 1);
        g.add_edge(WBASE+W*2+1, i, 1);
    }
    g.add_edge(CBASE+C*2, CBASE+C*2+1, Nc);

    for(int i = MBASE; i < MBASE+M*2; i += 2) {
        int k;
        cin >> k;
        while(k--) {
            int c;
            cin >> c;
            --c;
            g.add_edge(CBASE+c*2+1, i, 1);
        }
        g.add_edge(i, i+1, 1);
        g.add_edge(i+1, SINK, 1);
        g.add_edge(CBASE+C*2+1, i, 1);
    }
    g.add_edge(MBASE+M*2, MBASE+M*2+1, Nm);
    g.add_edge(MBASE+M*2+1, SINK, Nm);

    cout << g.dinic() << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
