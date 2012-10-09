//Name: Leonardo's Notebook
//Level: 3
//Category: 順列,置換,探索
//Note:

/*
 * ある置換(permutation)のうち，ABCD...に2回適用すると与えられた文字列のようになるものがあるか判定する．
 * ここで，たとえば初期状態でAの位置にあるものがBの位置に移動するものと仮定すると，2回目の置換でAが移動しなければいけない
 * 場所は決まっているので，結果として初期状態でBの位置にあるものがどこに移動するかも決まる．
 * これを続けていくと，正しい置換であれば最終的には移動先がAに戻ってくるはずである．
 * このようにして先頭から順に移動先を決めていけばよい．
 *
 * ただし，ナイーブにやるとO(N^N)になってしまい，実際ABCD....XZYのようなパターンでTLEする．
 * これは置換がすでに決まっている位置をビットで持ち，メモ化することで回避できる．
 *
 * オーダーはO(N^2 2^N)．ただしN=26．
 * また状態数O(2^N)は，実際には2^Nよりずっと小さいはずである．
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// assume perm[idx] == -1
bool check_perm(int idx, int to, vector<int> &perm, int &pat, const vector<int> &pos) {
    vector<int> modified;
    int pat_bak = pat;
    while(perm[idx] == -1) {
        perm[idx] = to;
        modified.push_back(idx);
        pat |= (1<<idx);
        int next_to = pos[idx];
        idx = to;
        to = next_to;
    }
    if(to != perm[idx]) {
        for(vector<int>::iterator it = modified.begin(); it != modified.end(); ++it) {
            perm[*it] = -1;
        }
        pat = pat_bak;
        return false;
    }
    return true;
}

set<int> memo;
bool dfs(int idx, vector<int> &perm, int &pat, const vector<int> &pos) {
    if(idx == 26) return true;
    if(memo.count(pat)) return false;
    if(perm[idx] != -1) return dfs(idx+1, perm, pat, pos);
    else {
        vector<int> backup(perm);
        for(int to = 0; to < 26; ++to) {
            if(check_perm(idx, to, perm, pat, pos)) {
                if(dfs(idx+1, perm, pat, pos)) return true;
                perm = backup;
            }
        }
    }
    memo.insert(pat);
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int N;
    cin >> N;
    while(N--) {
        string str;
        cin >> str;
        vector<int> pos(26, 0);
        for(int i = 0; i < 26; ++i) {
            pos[str[i]-'A'] = i;
        }
        vector<int> perm(26, -1);
        memo.clear();
        int pat = 0;
        if(dfs(0, perm, pat, pos)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
