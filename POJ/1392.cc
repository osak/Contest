//Name: Ouroboros Snake
//Level: 3
//Category: 探索
//Note:

/*
 * ウロボロス数に含まれるある数の下N-1桁と次の数の上N-1桁は同じであるから，各数をノードにしたグラフを描くと
 * どのノードも入ってくる辺が2本，出ていく辺が2本となる．
 * ここで全てのノードを1度づつ通るような経路を見つければよい．
 * ノード数に対してかなりグラフが疎なので普通に探索すると最小のウロボロス数が見つけられる．
 *
 * オーダーは不明．
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

bool dfs(int cur, vector<int> &sequence, vector<unsigned char> &visited, int N) {
    const int mask = (1<<(N-1)) - 1;
    int next = (cur&mask) << 1;

    visited[cur] = 1;
    sequence.push_back(cur);
    if((int)sequence.size() == (1<<N)) return true;

    if(!visited[next]) {
        if(dfs(next, sequence, visited, N)) return true;
    }
    next |= 1;
    if(!visited[next]) {
        if(dfs(next, sequence, visited, N)) return true;
    }
    sequence.pop_back();
    visited[cur] = 0;
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(true) {
        int N, K;
        cin >> N >> K;
        if(!N && !K) break;
        vector<unsigned char> visited(1<<N, 0);
        vector<int> sequence;
        dfs(0, sequence, visited, N);
        cout << sequence[K] << endl;
    }
    return 0;
}
