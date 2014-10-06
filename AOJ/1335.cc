//Name: Equal Sum Sets
//Level: 2
//Category: 数論,分割数,探索,メモ化,Memoize
//Note:

/**
 * 「n以下の数をk個使ってsを作る場合の数」を返す関数を考えると、状態数は NKS 個で抑えられる。
 * したがって、メモ化再帰の形で書き下せばよい。
 *
 * オーダーは O(N^2KS)。
 */
#include <iostream>
#include <array>

using namespace std;

int memo[21][11][156];
int dfs(int n, int k, int s) {
    if(s < 0) return 0;
    if(k == 0 && s == 0) return 1;
    if(n == 0) return 0;
    if(memo[n][k][s] != -1) return memo[n][k][s];
    memo[n][k][s] = 0;
    for(int i = n; i >= 1; --i) {
        memo[n][k][s] += dfs(i-1, k-1, s-i);
    }
    return memo[n][k][s];
}

bool solve() {
    int N, K, S;
    if(!(cin >> N >> K >> S)) return false;
    if(!N && !K && !S) return false;

    cout << dfs(N, K, S) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    for (int n = 0; n < 21; n++) {
        for (int k = 0; k < 11; k++) {
            for (int s = 0; s < 156; s++) {
                memo[n][k][s] = -1;
            }
        }
    }
    while(solve()) ;
    return 0;
}
