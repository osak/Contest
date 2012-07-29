//Name: Combination of Number Sequences
//Level: 3
//Category: 数え上げ,メモ化
//Note:

/*
 * 普通にnext_permutationの二重ループだと遅くて通らない．
 * dfsによるcombination全列挙+メモ化で通った．
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int memo[300][10][2048];

int dfs(int st, int depth, int N, int S, int used) {
    if(depth == N) {
        if(st == S) return 1;
        else return 0;
    }

    int &ans = memo[st][depth][used];
    if(ans >= 0) return ans;

    ans = 0;
    for(int i = 0; i < 10; ++i) {
        if(used & (1<<i)) continue;
        ans += dfs(st+i*(depth+1), depth+1, N, S, used | (1<<i));
    }
    return ans;
}

int main() {
    int N, S;
    while(cin >> N >> S) {
        memset(memo, -1, sizeof(memo));
        cout << dfs(0, 0, N, S, 0) << endl;
    }
    return 0;
}
