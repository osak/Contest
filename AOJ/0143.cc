//Name: Altair and Vega
//Level: 2
//Category: 幾何,Geometry,CCW
//Note:

/**
 * 三角形の内側の点pは、三角形の点a, b, cに対して
 *   ccw(a, p, b) = ccw(b, p, c) = ccw(c, p, a)
 * が成立し、またそのときに限ってpは三角形の内側にある。
 * ccwは外積の符号である。
 *
 * オーダーはO(N)。
 */
#include <iostream>
#include <complex>
#include <vector>

using namespace std;

typedef complex<double> P;

const double EPS = 1e-9;
const double PI = acos(-1);

inline double cross(const P &a, const P &b) {
    return a.real()*b.imag() - a.imag()*b.real();
}

inline int sgn(double a) {
    return a<0 ? -1 : 1;
}

void solve() {
    double x1, y1, x2, y2, x3, y3, xk, yk, xs, ys;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> xk >> yk >> xs >> ys;
    P a(x1, y1), b(x2, y2), c(x3, y3);
    P k(xk, yk), s(xs, ys);
    const int ca = sgn(cross(a-k, b-k)) + sgn(cross(b-k, c-k)) + sgn(cross(c-k, a-k));
    const int cb = sgn(cross(a-s, b-s)) + sgn(cross(b-s, c-s)) + sgn(cross(c-s, a-s));
    if((abs(ca) == 3 && abs(cb) != 3) || (abs(ca) != 3 && abs(cb) == 3)) cout << "OK" << endl;
    else cout << "NG" << endl;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    while(N--) solve();
    return 0;
}
