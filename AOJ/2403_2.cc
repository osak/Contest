//Name: The Enemy of My Enemy is My Friend
//Level: 3
//Category: 探索,メモ化,枝刈り
//Note:

/*
 * 前から順にノードを選んでいく．
 * 状態は
 * ・どのノードを見ているか
 * ・現在選べるノードの組
 * 普通に考えると後者が 2^40 あるが，実際には選んだノードの隣は選べなくなるため状態数はずっと少ない．
 * それでも全てのノードが独立な入力だと全パターン有効となるが，これは
 * 「この先選べるノードを全て選んだとしたときの点数」
 * を計算し，今までに見つかった最大値と比べて枝刈りに使う．
 *
 * オーダーは O(2^N) だが枝刈りがどのように効くか不明．
 */
#include <iostream>
#include <vector>
#include <tr1/unordered_map>
#include <map>
#include <string>

using namespace std;
using namespace tr1;

typedef long long LL;

struct Dict {
    map<string,int> dict;
    int id;

    Dict() : id(0) {}

    int get(const string &str) {
        if(dict.count(str)) return dict[str];
        return dict[str] = id++;
    }
};

struct Hasher {
    size_t operator ()(const pair<int,LL> &key) const {
        return key.first + key.second;
    }
};

unordered_map<pair<int,LL>,int,Hasher> memo;
int ans = 0;
void dfs(int pos, LL mask, int acc, const vector<int> &power, const vector<LL> &graph) {
    const int N = power.size();
    if(pos == N) {
        ans = max(ans, acc);
        return;
    }

    // これから先の可能なものを全て取っても，今までの最良解を超えられないなら枝刈り
    int expected = acc;
    for(int i = pos; i < N; ++i) {
        if(!(mask & (1LL<<i))) expected += power[i];
    }
    if(expected <= ans) return;

    pair<int,LL> key(pos, mask);
    if(memo.count(key) && memo[key] >= acc) return;
    memo[key] = acc;
    dfs(pos+1, mask, acc, power, graph);
    if(!(mask & (1LL<<pos))) {
        dfs(pos+1, mask | graph[pos], acc + power[pos], power, graph);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<int> power(N);
        vector<LL> graph(N);
        Dict dict;
        for(int i = 0; i < N; ++i) {
            int B, C;
            string cn;
            cin >> cn >> B >> C;
            int cid = dict.get(cn);
            power[cid] = B;
            while(C--) {
                string neighbor;
                cin >> neighbor;
                int nid = dict.get(neighbor);
                graph[cid] |= 1LL << nid;
            }
            graph[cid] |= 1LL << cid;
        }
        memo.clear();
        ans = 0;
        dfs(0, graph[0], power[0], power, graph);
        cout << ans << endl;
    }
    return 0;
}
