//Name: Name the Crossing
//Level: 4
//Category: グラフ,Graph,探索
//Note:

/*
 * 入力に従って有向辺を張ったグラフを作り，同水準条件を満たす頂点間には無向辺を張る．
 * また，隣接した頂点は異なる色になるように2色に色分けする．
 * このグラフ上でA-B間のパスが存在し，かつ頂点の色が異なればYES．
 *
 * オーダーは前処理に O(N^2), 判定が O(MN)．
 */
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct Node {
    int level;
    int color;
    int group;
    vector<int> edges, back_edges;
    vector<int> pending;
    Node() : level(0), color(1) {}
};

struct Dict {
    int idx;
    map<string,int> dict;

    Dict() : idx(0) {}
    int get(const string &str) {
        if(dict.count(str)) return dict[str];
        return dict[str] = idx++;
    }

    int size() const {
        return idx;
    }
};

#define FOREACH(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define TIMES(i,n) for(int (i) = 0; (i) < (n); ++(i))

typedef vector<unsigned char> Flag;

void preprocess(int pos, vector<Node> &nodes, Flag &visited, int group) {
    if(visited[pos]) return;
    visited[pos] = 1;

    Node &cur = nodes[pos];
    cur.group = group;
    FOREACH(it, cur.edges) {
        if(visited[*it]) continue;
        nodes[*it].level = cur.level+1;
        nodes[*it].color = 1 - cur.color;
        preprocess(*it, nodes, visited, group);
    }
    FOREACH(it, cur.back_edges) {
        if(visited[*it]) continue;
        nodes[*it].level = cur.level-1;
        nodes[*it].color = 1 - cur.color;
        preprocess(*it, nodes, visited, group);
    }
}

bool is_same_level(int a, int b, const vector<Node> &nodes) {
    vector<int> states(nodes.size(), 0);
    FOREACH(it, nodes[a].edges) {
        states[*it] |= 1;
    }
    FOREACH(it, nodes[b].edges) {
        states[*it] |= 2;
    }
    FOREACH(it, nodes[a].back_edges) {
        states[*it] |= 4;
    }
    FOREACH(it, nodes[b].back_edges) {
        states[*it] |= 8;
    }
    bool has_c = false, has_d = false;
    TIMES(i, nodes.size()) {
        if(i == a || i == b) continue;
        int state = states[i];
        if((state & 0x0c) == 0x0c || (state & 0x03) == 0x03) {
            has_c = true;
        }
        if((state & 0x09) == 0x09 || (state & 0x06) == 0x06) {
            has_d = true;
        }
    }
    return has_c && !has_d;
}

bool check(int from, int to, const vector<Node> &nodes, Flag &visited) {
    if(visited[from]) return false;
    if(from == to) return true;
    visited[from] = 1;
    const Node &cur = nodes[from];
    FOREACH(it, cur.edges) {
        if(check(*it, to, nodes, visited)) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<Node> nodes(2*N);
        Dict dict;
        TIMES(_, N) {
            string cross;
            cin >> cross;
            const int hyphen = cross.find('-');
            const int a = dict.get(cross.substr(0, hyphen));
            const int b = dict.get(cross.substr(hyphen+1));
            nodes[b].edges.push_back(a);
            nodes[a].back_edges.push_back(b);
        }
        N = dict.size();
        nodes.resize(N);
        Flag visited(N, 0);
        TIMES(i, N) {
            if(!visited[i]) {
                preprocess(i, nodes, visited, i);
            }
        }
        TIMES(i, N) {
            TIMES(j, i) {
                if(nodes[i].group == nodes[j].group) {
                    if(is_same_level(i, j, nodes)) {
                        nodes[i].pending.push_back(j);
                        nodes[j].pending.push_back(i);
                    }
                }
            }
        }
        TIMES(i, N) {
            nodes[i].edges.insert(nodes[i].edges.end(), nodes[i].pending.begin(), nodes[i].pending.end());
        }
        cout << N << endl;

        int M;
        cin >> M;
        TIMES(_, M) {
            string cross;
            cin >> cross;
            const int hyphen = cross.find('-');
            const int a = dict.get(cross.substr(0, hyphen));
            const int b = dict.get(cross.substr(hyphen+1));
            bool ans = true;
            if(a >= N || b >= N) {
                ans = false;
            } else if(nodes[a].group != nodes[b].group) {
                ans = false;
            } else if(nodes[a].color == nodes[b].color) {
                ans = false;
            } else {
                fill(visited.begin(), visited.end(), 0);
                ans = check(b, a, nodes, visited);
            }
            cout << (ans?"YES":"NO") << endl;
        }
    }
    return 0;
}
