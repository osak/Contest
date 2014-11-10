//Name: Tile
//Level: 2
//Cateogry: 数学
//Note:

/*
 * 線対称かつ点対称なので，左上区画に座標を正規化して考える．
 * 具体的にはfloor(N/2)の区画(大きさが奇数のときは中央を含むため)を考え，たとえばx座標がこの区画の幅をはみ出るときには
 * 元の正方形の右端からの距離を考え，これを左端からの距離として使うと左上区画に入る．
 * y座標も同様．
 * 色の判定は，左上隅から斜めに進んでいき，ある点から下か右に進むと考えればよい．
 *
 * オーダーは O(1)。
 */
#include <iostream>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    const int half = (N+1)/2;
    for(int i = 0; i < K; ++i) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        if(x >= half) {
            x = N-x-1;
        }
        if(y >= half) {
            y = N-y-1;
        }

        int level = min(x, y);
        cout << (level%3)+1 << endl;
    }
    return 0;
}
