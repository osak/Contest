//Name: Mobile Network
//Level: 3
//Category: グラフ,Graph,最大流
//Note:

/**
 * x^kの項に対する係数をL-k番目の要素としてもつようなvectorを考え、これを辞書順で最大にすればよい。
 * フローの型がベクトル値である以外は、普通の最大流で求められる。
 * ただし、residual flowがあるかどうかの判定は、0でない最高次の項の正負で判定する。
 *
 * オーダーは O(M^2 NL)。
 */
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <string>

using namespace std;

typedef vector<int> Poly;
namespace std {
    Poly& operator +=(Poly &a, const Poly &b) {
        for(int i = 0; i < a.size(); ++i) {
            a[i] += b[i];
        }
        return a;
    }
    Poly& operator -=(Poly &a, const Poly &b) {
        for(int i = 0; i < a.size(); ++i) {
            a[i] -= b[i];
        }
        return a;
    }
    Poly operator -(const Poly &a, const Poly &b) {
        Poly res = a;
        res -= b;
        return res;
    }
};

bool is_residual(const Poly &a) {
    for(int v : a) {
        if(v != 0) return v > 0;
    }
    return false;
}

const int L = 50;

template<class Flow>
struct Edge {
    int from, to;
    Flow capacity, flow;
    Edge *back;
    Edge() {}
    Edge(int from, int to, Flow c, Edge *b) : from(from), to(to), capacity(c), flow(Poly(L+1, 0)), back(b) {}
};

template<class Flow>
void make_edge(vector<vector<Edge<Flow>*>> &g, int src, int dst, Flow c) {
    auto *e = new Edge<Flow>(src, dst, c, nullptr);
    auto *back = e->back = new Edge<Flow>(dst, src, c, e);
    g[src].push_back(e);
    g[dst].push_back(back);
}

template <class T>
T dinic_augment(vector<vector<Edge<T>*>> &graph, vector<int> &level, vector<bool> &finished, int u, int sink, T cur)/*{{{*/
{
    if (u == sink || !is_residual(cur)) {
        return cur;
    }
    if (finished[u]) {
        return Poly(L+1, 0);
    }
    finished[u] = true;
    for(auto e : graph[u]) {
        if(e->capacity > e->flow && level[e->to] > level[u]) {
            const T f = dinic_augment(graph, level, finished, e->to, sink, min(cur, e->capacity - e->flow));
            if (is_residual(f)) {
                e->flow += f;
                e->back->flow -= f;
                finished[u] = false;
                return f;
            }
        }
    }
    return Poly(L+1, 0);
}/*}}}*/

// O(V^2 E)
template <typename T>
T dinic(vector<vector<Edge<T>*>> &graph, int source, int sink)/*{{{*/
{
    const int N = graph.size();
    T max_flow(L+1, 0);

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
                if (level[e->to] < 0 && e->capacity > e->flow) {
                    q.push(e->to);
                    level[e->to] = level[u] + 1;
                }
            }
        }

        fill(finished.begin(), finished.end(), false);
        bool updated = false;
        while (true) {
            const T f = dinic_augment<T>(graph, level, finished, source, sink, Poly(L+1, 100*500*100));
            if (!is_residual(f)) {
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

typedef string::const_iterator Iterator;
int number(Iterator &it) {
    int res = 0;
    while(isdigit(*it)) {
        res *= 10;
        res += *it - '0';
        ++it;
    }
    return res;
}

pair<int,int> term(Iterator &it) {
    pair<int,int> res(1, 0);
    if(isdigit(*it)) res.first = number(it);
    if(*it == 'x') {
        res.second = 1;
        ++it;
        if(*it == '^') {
            ++it;
            res.second = number(it);
        }
    }
    return res;
}

Poly parse(const string &s) {
    Iterator it = s.begin();
    Poly res(L+1, 0);
    do {
        const auto t = term(it);
        res[L-t.second] = t.first;
    } while(*it++ == '+');
    return res;
}

bool solve() {
    int N, M;
    cin >> N >> M;
    if(!N && !M) return false;

    vector<vector<Edge<Poly>*>> g(N);
    for(int i = 0; i < M; ++i) {
        int a, b;
        string expr;
        cin >> a >> b >> expr;
        --a; --b;
        make_edge(g, a, b, parse(expr));
    }
    const auto ans = dinic(g, 0, N-1);
    bool first = true;
    for(int i = 0; i <= L; ++i) {
        if(ans[i] != 0) {
            if(!first) cout << "+";
            if(ans[i] > 1 || i == L) cout << ans[i];
            const int ord = L - i;
            if(ord >= 1) {
                cout << "x";
                if(ord >= 2) {
                    cout << "^" << ord;
                }
            }
            first = false;
        }
    }
    if(first) cout << 0;
    cout << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
