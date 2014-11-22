//Name: Spellcasters
//Level: 2
//Category: 二分探索
//Note:

/**
 * r_i をソートしておき、各r_iについて、S-r_iより大きいものの個数を数えればよい。
 * このとき、(i,j)と(j,i)はすべて重複して数えているので、最後に2で割る。
 * r_i*2 > Sのときは(i,i)を数えてしまうので、忘れずに取り除く。
 *
 * オーダーは O(N log N)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool solve() {
    int N, S;
    if(!(cin >> N >> S)) return false;
    if(!N && !S) return false;

    vector<int> rs(N);
    for(int i = 0; i < N; ++i) {
        cin >> rs[i];
    }
    sort(begin(rs), end(rs));

    int ans = 0;
    for(int i = 0; i < N; ++i) {
        ans += distance(lower_bound(begin(rs), end(rs), S-rs[i]+1), end(rs));
        if(rs[i]*2 > S) --ans;
    }
    cout << ans/2 << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
