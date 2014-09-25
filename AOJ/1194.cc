//Name: Vampire
//Level: 2
//Category: 幾何
//Note:

/**
 * 第一象限に注目すると、太陽のうち区間[x,x+1)にある箇所が影から出るとき、
 * もっとも早く出るのは座標xの点である（太陽の中心、建物の座標がともに整数であり、太陽は上に凸であるため）。
 * したがって、[x,x+1)が影から出るイベントに対しては、xで太陽がはみ出る時刻のみを調べればよい（このとき、xが建物の右端でも出ていると判定することに注意）。
 * 第二象限についても同様。
 *
 * オーダーはO(R)。
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

bool solve() {
    int R, N;
    if(!(cin >> R >> N)) return false;
    if(!R && !N) return false;

    vector<int> hs(R+1), nhs(R+1);
    for(int i = 0; i < N; ++i) {
        int xl, xr, h;
        cin >> xl >> xr >> h;
        for(int x = max(0, xl); x < xr; ++x) {
            if(0 <= x && x <= R) hs[x] = max(hs[x], h);
        }
        for(int x = min(0, xr); x > xl; --x) {
            if(0 <= -x && -x <= R) nhs[-x] = max(nhs[-x], h);
        }
    }
    double ans = 1000000;
    for(int x = 0; x < R; ++x) {
        const double t = hs[x] + R - sqrt(R*R - x*x);
        ans = min(ans, t);
    }
    for(int x = 0; x > -R; --x) {
        const double t = nhs[-x] + R - sqrt(R*R - x*x);
        ans = min(ans, t);
    }
    cout.precision(10);
    cout << fixed << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
