//Name: The Child and Toy
//Level: 2
//Category: グラフ,Graph,貪欲,Greedy
//Note:

/**
 * パーツを外す時は必ずロープをすべて切ることになる。
 * ロープを切るコストは、その両端にあるパーツのどちらかのコストであるから、
 * 高いパーツがなるべく存在しないほうがよい。
 * したがって、高いパーツから順に外していけば良い。
 * このとき、全てのロープを安い方のコストで切ることができる。
 *
 * オーダーは O(N+M)。
 */
#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef long long LL;

bool solve() {
    int N, M;
    if(!(cin >> N >> M)) return false;
    vector<int> costs(N);
    for(int i = 0; i < N; ++i) {
        cin >> costs[i];
    }
    LL res = 0;
    for(int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        res += min(costs[a-1], costs[b-1]);
    }
    cout << res << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
