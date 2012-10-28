//Name: The Maximum Number of Strong Kings
//Level: 3
//Category: グラフ,Graph
//Note:

/*
 * あるスコアでStrongであるためには，それより大きいスコアのノードに辺を張らなければならない．
 * したがって，自分より大きいスコアのノードの個数は自分のスコア以下である必要がある．
 * また，上位ノードが辺を張ると，張られたノードは決してStrongになれない．
 * よって，Strongになり得るノードにはなるべく辺を張らないようにして場所を決めていくと
 * Strongになるノード数を最大化できる．
 *
 * 最大スコアでないノードでは，自分のスコアで全ての上位ノードに辺を張れるかを確認しないといけないことに注意．
 * オーダーは O(N^3)．
 * 下記実装では手付かずのノード判定を適当にやっているため O(N^4) になっている．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <numeric>

using namespace std;

int place_here(int pos, int edges, vector<vector<int> > &refered_by, vector<int> &used, bool really) {
    const int N = used.size();
    int cost = (accumulate(refered_by[pos].begin(), refered_by[pos].end(), 0) > 0) ? 0 : 1;
    int edge_remain = edges;
    // すでにどこかから参照されているノード or 使用済みノードを優先的に消費する．
    for(int j = 0; edge_remain > 0 && j < N; ++j) {
        if(j == pos) continue;
        if(refered_by[pos][j]) continue; // すでに逆向きの辺が張られている
        if(used[j] || accumulate(refered_by[j].begin(), refered_by[j].end(), 0) > 0) {
            if(really) {
                //cout << "edge " << pos << "->" << j << endl;
                refered_by[j][pos] = 1;
            }
            --edge_remain;
        }
    }
    //if(really) cout << "rem: " << edge_remain << ' ' << pos << endl;
    // まだノードを追加する必要があれば，新しいノードに辺を張る．
    for(int j = 0; edge_remain > 0 && j < N; ++j) {
        if(j == pos) continue;
        if(refered_by[pos][j]) continue; // すでに逆向きの辺が張られている
        if(accumulate(refered_by[j].begin(), refered_by[j].end(), 0) == 0) {
            ++cost;
            --edge_remain;
            if(really) {
                refered_by[j][pos] = 1;
                //cout << "place " << j << endl;
            }
        }
    }
    if(really) used[pos] = 1;
    if(edge_remain > 0) cost = N+1;
    return cost;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int M;
    cin >> M;
    cin.ignore();
    while(M--) {
        string line;
        getline(cin, line);
        vector<int> scores;
        istringstream is(line);
        while(!is.eof()) {
            int val;
            is >> val;
            scores.push_back(val);
        }
        const int N = scores.size();
        sort(scores.begin(), scores.end());
        vector<vector<int> > refered_by(N, vector<int>(N, 0));
        vector<int> used(N, 0);
        int ans = 0;
        for(vector<int>::reverse_iterator it = scores.rbegin(); it != scores.rend(); ++it) {
            if(*it == scores.back()) {
                // 置き場所をきめる
                int best_pos = -1;
                int best_cost = N+1;
                for(int i = 0; i < N; ++i) {
                    if(used[i]) continue;
                    int cost = place_here(i, *it, refered_by, used, false);
                    if(cost < best_cost) {
                        best_pos = i;
                        best_cost = cost;
                    }
                }
                // 実際に置く
                {
                    place_here(best_pos, *it, refered_by, used, true);
                    ++ans;
                }
            } else {
                // 空いているノードがあり，かつ辺数が上位ノードの数より多いならstrongになれる．
                // このとき参照はシミュレートしなくてもよい(どうせ張れるので)
                int pos;
                for(pos = 0; pos < N; ++pos) {
                    if(!used[pos] && accumulate(refered_by[pos].begin(), refered_by[pos].end(), 0) == 0) {
                        break;
                    }
                }
                if(pos == N) break;
                int cnt = 0;
                for(vector<int>::reverse_iterator it2 = scores.rbegin(); it2 != scores.rend() && *it2 > *it; ++it2) {
                    ++cnt;
                }
                if(*it >= cnt) {
                    used[pos] = 1;
                    ++ans;
                } else {
                    break;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
