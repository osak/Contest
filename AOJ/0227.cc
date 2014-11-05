//Name: Thanksgiving
//Level: 2
//Category: 貪欲,Greedy
//Note:

/*
 * 野菜を価格の順に並べたとき、取り除ける個数は floor(n/m) 個で固定であることから、
 * 安いほうから n%m 個までの野菜は取り除いても効率が悪い。
 * したがって、残った n - n%m 個の野菜から floor(n/m) 個を取り除くことになるが、
 * このときもっとも安い野菜は必ず取り除かれることになる。
 * この野菜と一緒に袋に詰められる野菜は可能な限り安いものを使ったほうがよい（なるべく高い野菜を次で消せるようにする）から、
 * 結局貪欲に詰めていけばよい。
 *
 * 高い野菜からm個ずつ選んでいくようにすると楽に書ける。
 *
 * オーダーは O(N log N)。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool solve() {
    int N, M;
    if(!(cin >> N >> M)) return false;
    if(!N && !M) return false;

    vector<int> ps(N);
    for(int i = 0; i < N; ++i) {
        cin >> ps[i];
    }
    sort(begin(ps), end(ps), greater<int>());

    int ans = 0;
    for(int i = 0; i < N; ++i) {
        if(i % M == M-1) continue;
        ans += ps[i];
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
