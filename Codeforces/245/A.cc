//Name: Xor-tree
//Level: 2
//Category: グラフ,Graph,木,Tree,シミュレーション
//Note:

/**
 * 木の根から貪欲に反転させていくのが最適かつ、これ以外の方法はない。
 * あるノードを反転させたとき、その子への影響は深さのmod 2でループしている。
 * したがって、それぞれの深さについて反転するかしないかを状態として持ちつつDFSすればよい。
 *
 * オーダーはO(N)。
 */
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

array<vector<int>,100000> tree;

void dfs(int v, int parent, int flip, int flip_next, const vector<int> &target, vector<int> &hist) {
    if(flip != target[v]) {
        flip ^= 1;
        hist.push_back(v);
    }
    for(auto nv : tree[v]) {
        if(nv == parent) continue;
        dfs(nv, v, flip_next, flip, target, hist);
    }
}

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    for(int i = 0; i < N; ++i) {
        tree[i].clear();
    }
    for(int i = 0; i < N-1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    vector<int> target(N);
    for(int i = 0; i < N; ++i) {
        cin >> target[i];
    }
    for(int i = 0; i < N; ++i) {
        int v;
        cin >> v;
        target[i] ^= v;
    }
    vector<int> res;
    dfs(0, -1, 0, 0, target, res);
    sort(res.begin(), res.end());
    cout << res.size() << endl;
    for(int i : res) {
        cout << i+1 << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
