//Name: The Maximum Number of Strong Kings
//Level: 3
//Category: グラフ,Graph
//Note:

/*
 * あるスコアでStrongであるためには，それより大きいスコアのノードに辺を張らなければならない．
 * したがって，自分より大きいスコアのノードの個数は自分のスコア以下である必要がある．
 * また，上位ノードが辺を張ると，張られたノードは決してStrongになれない．
 * このときの候補の減り方は
 * ・最初の最大ノードは自分の場所+辺を張る場所で s_i + 1 消費する
 * ・2個目の最大ノードは1個目が辺を張った場所に入るが，1個目には辺を張れないので 1 ノード消費する
 * ・3個目以降の最大ノードは既に辺が張られているノードと最大ノードだけで全ての辺が張れるので，余分なノードを消費しない
 * となる．
 *
 * オーダーは O(N)．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

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
        int room = N;
        int ans = 0;
        int max_cnt = 0;
        for(vector<int>::reverse_iterator it = scores.rbegin(); it != scores.rend(); ++it) {
            if(*it == scores.back()) {
                if(max_cnt == 0) {
                    room -= *it;
                    --room;
                } else if(max_cnt == 1) {
                    --room;
                }
                ++ans;
                ++max_cnt;
            } else {
                if(room > 0) {
                    if(it - scores.rbegin() <= *it) {
                        --room;
                        ++ans;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
