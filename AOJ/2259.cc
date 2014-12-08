//Name: Programming Contest
//Level: 1
//Category: やるだけ
//Note:

/**
 * 行ごとに1の個数の総和を求める。
 *
 * オーダーは O(MN)。
 */
#include <iostream>
#include <algorithm>

using namespace std;

bool solve() {
    int M, N;
    if(!(cin >> M >> N)) return false;

    int ans = 0;
    for(int i = 0; i < M; ++i) {
        int sum = 0;
        for(int j = 0; j < N; ++j) {
            int v;
            cin >> v;
            sum += v;
        }
        ans = max(ans, sum);
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
