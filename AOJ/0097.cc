//Name: Sum of Integers II
//Level: 2
//Category: 数学,数え上げ,分割数,メモ化再帰
//Note:

/**
 * いわゆる分割数。
 *
 * f(k,m,s) = m以上の数をk個使ってsを作るパターン数
 * として、メモ化再帰を書く。
 *
 * オーダーは O(NMS)。
 * ただし、Mは使える数の種類数で、M=101。
 */
#include <iostream>
#include <algorithm>

using namespace std;

long long memo[10][102][1001];
bool visited[10][102][1001];

long long calc(int k, int m, int s) {
    if(k == 0) return s == 0;
    if(s < 0) return 0;
    if(visited[k][m][s]) return memo[k][m][s];

    visited[k][m][s] = true;
    for(int i = m; i <= min(s, 100); ++i) {
        memo[k][m][s] += calc(k-1, i+1, s-i);
    }
    return memo[k][m][s];
}

bool solve() {
    int N, S;
    if(!(cin >> N >> S)) return false;
    if(!N && !S) return false;
    cout << calc(N, 0, S) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) ;
    return 0;
}
