//Name: SHEET
//Level: 3
//Category: グラフ,Graph,有向グラフ,閉路検出,DAG判定
//Note:

/*
 * 演算は関係なく，セルの参照関係のみから有向グラフを作って閉路があるか判定すればよい．
 * また，既に判定したノードに到達した場合は枝刈りできる．
 *
 * オーダーは O(M)．
 * ただしMはグラフの辺数 ≒ 入力の右辺のセル数．
 */
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <set>

using namespace std;

#define FOREACH(it,c) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)

enum State {
    UNDEFINED, NONE, VISITED, OK, CIRCULAR
};

int cell2node(const string &str) {
    const string row = str.substr(1, 2);
    const string col = str.substr(4, 2);
    return (atoi(row.c_str())-1)*20 + atoi(col.c_str())-1;
}

State dfs(int pos, const vector<set<int> > &graph, vector<State> &state) {
    state[pos] = VISITED;
    FOREACH(it, graph[pos]) {
        if(state[*it] == VISITED || state[*it] == CIRCULAR) return state[pos] = CIRCULAR;
        if(state[*it] == OK) continue;
        State ret = dfs(*it, graph, state);
        if(ret == CIRCULAR) return state[pos] = CIRCULAR;
    }
    return state[pos] = OK;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string line;
    vector<set<int> > graph(400);
    vector<int> cells;
    vector<State> state(400, UNDEFINED);
    while(getline(cin, line)) {
        const string cellstr = line.substr(0, 6);
        const int node = cell2node(cellstr);
        cells.push_back(node);
        state[node] = NONE;
        size_t pos = 7;
        while((pos = line.find('R', pos)) != string::npos) {
            const string refstr = line.substr(pos, 6);
            graph[node].insert(cell2node(refstr));
            pos += 6;
        }
    }

    FOREACH(it, cells) {
        if(state[*it] == NONE) {
            dfs(*it, graph, state);
        }
    }
    FOREACH(it, cells) {
        printf("R%02dC%02d %s\n", *it/20+1, *it%20+1, state[*it] == CIRCULAR ? "circular" : "ok");
    }

    return 0;
}
