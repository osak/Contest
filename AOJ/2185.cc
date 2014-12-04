//Name: Petting Cats
//Level: 1
//Category: やるだけ
//Note:

/*
 * 点が矩形に含まれているか判定するだけ。
 *
 * オーダーは O(N)。
 */
#include <iostream>

using namespace std;

void solve() {
    int X, Y, W, H;
    cin >> X >> Y >> W >> H;
    int N;
    cin >> N;
    int ans = 0;
    for(int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        ans += (X <= x && x <= X+W && Y <= y && y <= Y+H);
    }
    cout << ans << endl;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    while(N--) solve();
    return 0;
}
