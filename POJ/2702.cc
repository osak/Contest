//Name: Can a Complicated Program Go Wrong?
//Level: 3
//Category: グラフ,Graph,幅優先探索
//Note:

/*
 * 2つのオートマトンのノードの組を状態にして幅優先探索する．
 * 1つめのオートマトンにない遷移は考えないことに注意．
 *
 * オーダーは O(S^2)．
 */ 
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

struct FSM {
    int start;
    vector<map<char,int> > edges;

    FSM() {}
    FSM(int size) : edges(size) {}

    void set_size(int size) {
        edges.resize(size);
    }

    void add_edge(int node, char c, int to) {
        edges[node][c] = to;
    }

    int run(int node, char act) {
        if(edges[node].count(act)) return edges[node][act];
        return -2;
    }

    int size() const {
        return edges.size();
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
    cin >> N;
    while(N--) {
        FSM fsm[2];
        for(int i = 0; i < 2; ++i) {
            int S, E;
            cin >> S >> E >> fsm[i].start;
            fsm[i].start--;
            fsm[i].set_size(S);
            while(E--) {
                int node, to;
                char act;
                cin >> node >> act >> to;
                --node;
                if(to > 0) --to;
                fsm[i].add_edge(node, act, to);
            }
        }
        vector<vector<unsigned char> > memo(fsm[0].size(), vector<unsigned char>(fsm[1].size(), 0));
        queue<pair<int,int> > q;
        q.push(make_pair(fsm[0].start, fsm[1].start));
        memo[fsm[0].start][fsm[1].start] = 1;
        bool ok = true;
        while(!q.empty()) {
            const pair<int,int> state = q.front();
            q.pop();
            for(char act = 'a'; act <= 'z'; ++act) {
                const int to_0 = fsm[0].run(state.first, act);
                int to_1 = fsm[1].run(state.second, act);
                if(to_0 == -2) continue;
                if(to_1 == -2) to_1 = state.second;
                if(to_1 == -1) {
                    ok = false;
                    goto end;
                }
                if(!memo[to_0][to_1]) {
                    memo[to_0][to_1] = 1;
                    q.push(make_pair(to_0, to_1));
                }
            }
        }
end:
        cout << (ok?"satisfied":"violated") << endl;
    }
    return 0;
}
