//Name: Never Wait for Weights
//Level: 3
//Category: Union Find
//Note:

/**
 * Union Findしながら、根との距離をメンテナンスすればよい。
 *
 * オーダーはO(M log N)。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

typedef long long LL;
struct Node {
    int root;
    LL diff;
};

int root(int n, vector<Node> &nodes) {
    if(nodes[n].root == n) return n;
    const int r = root(nodes[n].root, nodes);
    nodes[n].diff += nodes[nodes[n].root].diff;
    return nodes[n].root = r;
}

bool unite(int a, int b, vector<Node> &nodes, LL w) {
    const int ra = root(a, nodes);
    const int rb = root(b, nodes);
    if(nodes[ra].root == nodes[rb].root) return false;
    nodes[ra].root = nodes[rb].root;
    nodes[ra].diff = w - nodes[a].diff + nodes[b].diff;
    return true;
}

bool solve() {
    int N, M;
    cin >> N >> M;
    if(!N && !M) return false;

    vector<Node> nodes(N);
    for(int i = 0; i < N; ++i) {
        nodes[i].root = i;
        nodes[i].diff = 0;
    }
    for(int i = 0; i < M; ++i) {
        string cmd;
        cin >> cmd;
        if(cmd == "!") {
            int a, b, w;
            cin >> a >> b >> w;
            --a; --b;
            unite(a, b, nodes, w);
        } else {
            int a, b;
            cin >> a >> b;
            --a; --b;
            root(a, nodes);
            root(b, nodes);
            if(nodes[a].root != nodes[b].root) {
                cout << "UNKNOWN" << endl;
            } else {
                const LL diff = nodes[a].diff - nodes[b].diff;
                cout << diff << endl;
            }
        }
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
