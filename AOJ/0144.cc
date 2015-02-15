//Name: Packet Transportation
//Level: 2
//Category: グラフ,Graph,全点対間最短距離
//Note:

/**
 * 全点対間の最短距離を求めておけば良い。
 * オーダーは O(N^3)。
 */
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
struct Maybe {/*{{{*/
    T val;
    bool valid;

    Maybe() : valid(false) {}
    Maybe(T &t) : val(t), valid(true) {}

    const T& operator =(const T &rv) {
        val = rv;
        valid = true;
        return val;
    }

    operator T() const {
        return valid ? val : T();
    }

    template<typename Cond>
    bool update(const T &v, Cond cond) {
        if(!valid || cond(v, val)) {
            val = v;
            valid = true;
            return true;
        }
        return false;
    }

    bool update(const T &v) {
        return update(v, less<T>());
    }
};/*}}}*/

template<typename T>
struct WarshallFloyd {
    vector<vector<Maybe<T>>> graph;
    int N;

    WarshallFloyd(int size) : graph(size), N(size) {
        for(auto &v : graph) {
            v.resize(size);
        }
    }

    void add_edge(int from, int to, const T &dist) {
        graph[from][to] = dist;
    }

    void freeze() {
        for(int k = 0; k < N; ++k) {
            for(int i = 0; i < N; ++i) {
                for(int j = 0; j < N; ++j) {
                    if(graph[i][k].valid && graph[k][j].valid) {
                        graph[i][j].update(graph[i][k] + graph[k][j]);
                    }
                }
            }
        }
    }

    const Maybe<T>& query(int from, int to) {
        return graph[from][to];
    }
};

bool solve(bool first) {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    WarshallFloyd<int> wf(N);
    for(int i = 0; i < N; ++i) {
        int from, k;
        cin >> from >> k;
        --from;
        while(k--) {
            int v;
            cin >> v;
            wf.add_edge(from, v-1, 1);
        }
    }
    wf.freeze();
    int P;
    cin >> P;
    while(P--) {
        int s, d, t;
        cin >> s >> d >> t;
        const auto &dist = wf.query(s-1, d-1);
        if(dist.valid && dist+1 <= t) {
            cout << dist+1 << endl;
        } else {
            cout << "NA" << endl;
        }
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(2);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
