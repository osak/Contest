//Name: Space-Time Sugoroku Road
//Level: 3
//Category: 探索,メモ化
//Note:

/*
 * それぞれのマスについて最短到達ターン数を覚えておき，それより大きいターン数での到達は無視する．
 * この枝刈りを加え，後はサイコロの出目でBFSするだけ．
 *
 * 1度通ったマスに再び入ることはないので，オーダーは O(N)．
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int v[100000];
int memo[100000];
int N;
int ans;

void simulate(int pos, int dice, int turn, queue<int> &q) {
    int next = pos+dice;
    if(next >= N-1) {
        ans = min(ans, turn);
        return;
    } 
    if(memo[next] <= turn) return; // already visited
    memo[next] = turn;
    if(v[next] == 0) {
        // 次の開始点として使用可能
        q.push(next);
    } else {
        simulate(next, v[next], turn, q);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin >> N;
    for(int i = 0; i < N; ++i) {
        cin >> v[i];
        memo[i] = N;
    }
    ans = N;
    memo[0] = 0;
    queue<int> q;
    q.push(0);
    while(!q.empty()) {
        int pos = q.front();
        q.pop();
        for(int dice = 1; dice <= 6; ++dice) {
            simulate(pos, dice, memo[pos]+1, q);
        }
    }

    cout << ans << endl;
}
