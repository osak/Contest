//Name: Dictionary
//Level: 2
//Category: グラフ,Graph,DAG
//Note:

/**
 * 文字列が辞書順に並んでいるとしたとき、隣り合った文字列の最初に異なった文字の大小関係がわかる。
 * これを使ってグラフを作ったとき、サイクルが存在しなければよい。
 *
 * オーダーはO(N + C^2)。
 * ただしCはアルファベットの文字数で、C=26。
 */
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

bool dfs(int pos, int start, const vector<vector<int>> &graph, vector<bool> &visited) {
    if(visited[pos]) return false;

    visited[pos] = true;
    for(int v : graph[pos]) {
        if(v == start) return true;
        if(dfs(v, start, graph, visited)) return true;
    }
    return false;
}

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<string> v(N);
    for(int i = 0; i < N; ++i) {
        cin >> v[i];
    }
    vector<vector<int>> graph(26);
    for(int i = 0; i < N-1; ++i) {
        const string &s1 = v[i];
        const string &s2 = v[i+1];
        if(s1.size() > s2.size() && s1.substr(0, s2.size()) == s2) {
            cout << "no" << endl;
            return true;
        }
        for(int j = 0; j < s1.size() && j < s2.size(); ++j) {
            if(s1[j] != s2[j]) {
                graph[s1[j]-'a'].push_back(s2[j]-'a');
                break;
            }
        }
    }
    for(int i = 0; i < 26; ++i) {
        vector<bool> visited(26, false);
        if(dfs(i, i, graph, visited)) {
            cout << "no" << endl;
            return true;
        }
    }
    cout << "yes" << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
