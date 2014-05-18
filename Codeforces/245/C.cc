//Name: Guess the Tree
//Level: 3
//Category: 探索
//Note:

/**
 * ノード数の小さいほうから大きい方に向けて、可能な部分木の構成をすべて試していく。
 * 部分木の構成方法は、分割数の列挙と同様に再帰的にして全部列挙すればよい。
 * また、葉でないノードが必ず2個以上の子をもたないといけないという制約に注意する。
 *
 * このとき、どのノードを作っているかと、その時点で使われていないノードの組み合わせが決まれば、答えは一意に定まる。
 * したがって、状態数は高々 N * 2^N であるから、既に到達した状態を覚えておくことで枝刈りができる。
 *
 * オーダーは O(N ✕ |c|^2 2^N)。
 * ただし、分割数列挙のオーダーを O(N^2)で見積もっている。
 */
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

bool dfs(int, vector<int>&, const vector<int>&);

bool dfs_inner(int v, vector<int> &state, const vector<int> &nodes, int target, int k) {
    //cout << v << ' ' << target << ' ' << k << ' ' << state[1] << endl;
    for(int i = k; i <= 24; ++i) {
        if(state[i] == 0) continue;
        if(nodes[v]-1 == target && i == target) break;
        for(int use = 0; use <= state[i]; ++use) {
            const int rem = target - i * use;
            if(rem < 0) break;
            state[i] -= use;
            if(rem == 0) {
                state[nodes[v]]++;
                if(dfs(v+1, state, nodes)) return true;
                state[nodes[v]]--;
            } else {
                if(dfs_inner(v, state, nodes, rem, k+1)) return true;
            }
            state[i] += use;
        }
        break;
    }
    return false;
}

set<vector<int>> memo;
bool dfs(int v, vector<int> &state, const vector<int> &nodes) {
    const int N = nodes.size();
    if(v == N) {
        for(int i = 1; i <= 24; ++i) {
            if(i == nodes[v-1] && state[i] != 1) return false;
            if(i != nodes[v-1] && state[i] != 0) return false;
        }
        return true;
    }
    if(memo.count(state)) return false;
    memo.insert(state);
    const int target = nodes[v];
    if(target == 1) {
        state[1]++;
        if(dfs(v+1, state, nodes)) return true;
        state[1]--;
    } else {
        if(dfs_inner(v, state, nodes, target-1, 1)) return true;
    }
    return false;
}

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<int> nodes(N);
    for(int i = 0; i < N; ++i) {
        cin >> nodes[i];
    }
    sort(nodes.begin(), nodes.end());
    vector<int> state(25, 0);
    memo.clear();
    if(dfs(0, state, nodes)) cout << "YES" << endl;
    else cout << "NO" << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
