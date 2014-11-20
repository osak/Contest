//Name: Sum of 4 Integers II
//Level: 2
//Category: 数学,数え上げ,メモ化再帰
//Note:

/**
 * f(k,n) = k個の数を使ってnを作るパターン数
 * として、メモ化再帰を書く。
 *
 * オーダーは O(N^2K)。
 * ただし、Kは使う整数の個数で、K=4。
 */
#include <iostream>
#include <algorithm>

using namespace std;

int memo[5][4001];
bool visited[5][4001];

int calc(int k, int n) {
    if(k == 0) return n == 0;
    if(visited[k][n]) return memo[k][n];

    visited[k][n] = true;
    for(int i = 0; i <= min(n, 1000); ++i) {
        memo[k][n] += calc(k-1, n-i);
    }
    return memo[k][n];
}

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    cout << calc(4, N) << endl;
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
