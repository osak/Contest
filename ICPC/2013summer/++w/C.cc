//Name: Wave Attack
//Level: 4
//Category: 幾何,二分探索
//Note:

/*
 * 反射を考える問題なので、(X,Y)を中心とした円が、(P,Q)を鏡像対称にたくさん並べたものを
 * いくつ含むかという問題に帰着できる。
 * (P,Q)の複製のうち、x=P+αであるものについて考えると、円に含まれる上限、下限のy座標を
 * 二分探索によって求めることができる。
 * (P+α, y_max)から(P+α, y_min)までの点はすべて円内に含まれるから、すべての可能なP+αについて
 * 同じ計算を繰り返すことで答えが求められる。
 *
 * オーダーはO(VH/W log (VH/Y))。
 */
#include <iostream>

using namespace std;

typedef long long LL;

bool in_circle(LL x, LL y, LL cx, LL cy, LL r) {
    return (x-cx)*(x-cx) + (y-cy)*(y-cy) <= r*r;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int W, H, V, T, X, Y, P, Q;
    cin >> W >> H >> V >> T >> X >> Y >> P >> Q;

    const int R = V*T;
    const int DX1 = P*2;
    const int DX2 = (W-P)*2;
    const int DY1 = Q*2;
    const int DY2 = (H-Q)*2;

    LL ans = 0;
    int x = P, phase = 0;
    while(in_circle(x, Q, X, Y, R)) {
        if(phase == 0) x -= DX1;
        else x -= DX2;
        phase ^= 1;
    }
    do {
        if(phase == 1) x += DX1;
        else x += DX2;
        phase ^= 1;
        if(!in_circle(x, Q, X, Y, R)) break;

        int left = 0, right = R;
        while(left+1 < right) {
            const int center = (left+right) / 2;
            const int y = Q + H*(center-1) + (center % 2 == 0 ? H : DY2);
            if(in_circle(x, y, X, Y, R)) {
                left = center;
            } else {
                right = center;
            }
        }
        const int top = left;
        left = 0;
        right = R;
        while(left+1 < right) {
            const int center = (left+right) / 2;
            const int y = Q - H*(center-1) - (center % 2 == 0 ? H : DY1);
            if(in_circle(x, y, X, Y, R)) {
                left = center;
            } else {
                right = center;
            }
        }
        const int bottom = left;
        ans += top + bottom + 1;
    } while(true);
    cout << ans << endl;
    return 0;
}
