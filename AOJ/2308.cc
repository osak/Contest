//Name: White Bird
//Level: 4
//Category: 幾何,Geometry
//Note:

/**
 * 射出角度は、(X,Y)に直接ぶつけるか、障害物の上側頂点を通るものだけを考えればよい。
 * （下側頂点をちょうど通るようなものは、更に下げても有効である）
 *
 * 目標地点Pが決まると、初速のx成分とy成分を分けて考えることで、
 *   Px = Vx × t
 *   Py = -4.9t^2 + Vy × t
 *   Vx^2 + Vy^2 = V^2
 * という連立方程式になり、これを解くことで2つの候補が出てくる。
 * それぞれについて、Xより前で障害物と軌道が衝突せず、X地点で
 * Yより上にいることを確認すればよい。
 *
 * オーダーはO(N^2)。
 */
#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#include <cmath>

using namespace std;

typedef complex<double> P;

const double EPS = 1e-9;

int cmp(double a, double b) {
    const double diff = a-b;
    if(fabs(diff) < EPS) return 0;
    return diff < 0 ? -1 : 1;
}

struct Rect {
    P lb, rt;

    Rect() {}
    Rect(const P &lb, const P &rt) : lb(lb), rt(rt) {}

    double top() const { return rt.imag(); }
    double bottom() const { return lb.imag(); }
    double left() const { return lb.real(); }
    double right() const { return rt.real(); }
};

double calc(double t, double vy) {
    return -4.9*t*t + vy*t;
}

bool shoot(double vx, double vy, const vector<Rect> &rects, double X, double Y) {
    if(cmp(vx, 0) == 0) {
        return cmp(Y, 0) == 0;
    }
    // X地点でY上空にいられない
    if(cmp(calc(X / vx, vy), Y) < 0) return false;

    const double top_t = vy / 9.8;
    const double top_x = vx * top_t;
    const double top_y = calc(top_t, vy);
    for(const Rect &r : rects) {
        const double y_left = calc(r.left()/vx, vy);
        const double y_right = calc(r.right()/vx, vy);
        // Crash into left wall
        if(cmp(r.bottom(), y_left) < 0 && cmp(y_left, r.top()) < 0) return false;
        // Crash into right wall
        if(cmp(r.bottom(), y_right) < 0 && cmp(y_right, r.top()) < 0) return false;
        // Crash into top wall
        if(cmp(y_left, r.top()) >= 0) {
            if(cmp(y_right, r.top()) < 0) return false;
        }
        // Crash into bottom wall
        if(cmp(y_left, r.bottom()) <= 0) {
            if(cmp(y_right, r.bottom()) > 0) return false;
        }
        // Crash into bottom wall(2)
        if(cmp(r.left(), top_x) < 0 && cmp(top_x, r.right()) < 0) {
            if(cmp(y_left, r.bottom()) <= 0
                && cmp(y_right, r.bottom()) <= 0
                && cmp(top_y, r.bottom()) > 0) return false;
        }
    }
    return true;

}
bool check(const P &aim, const vector<Rect> &rects, double V, double X, double Y) {
    const double a = norm(aim);
    const double b = 9.8*aim.imag()*aim.real()*aim.real() - V*V*aim.real()*aim.real();
    const double c = 4.9*4.9*pow(aim.real(), 4);
    const double D = b*b - 4*a*c;
    //cout << D << endl;
    if(D < 0) return false;
    const double vx_1 = 4*a*c / (2*a*(-b-sqrt(D)));
    if(vx_1 >= 0) {
        const double vx = sqrt(vx_1);
        const double vy = sqrt(V*V - vx_1);
        if(shoot(vx, vy, rects, X, Y)) return true;
    }
    const double vx_2 = (-b - sqrt(D)) / (2*a);
    if(vx_2 >= 0) {
        const double vx = sqrt(vx_2);
        const double vy = sqrt(V*V - vx_2);
        if(shoot(vx, vy, rects, X, Y)) return true;
    }
    return false;
}

bool solve() {
    int N, V, X, Y;
    if(!(cin >> N >> V >> X >> Y)) return false;

    vector<Rect> rects;
    for(int i = 0; i < N; ++i) {
        double l, b, r, t;
        cin >> l >> b >> r >> t;
        if(l > X) continue;
        if(r > X) r = X;
        rects.push_back(Rect(P(l, b), P(r, t)));
    }
    if(check(P(X, Y), rects, V, X, Y)) {
        cout << "Yes" << endl;
        return true;
    }

    for(const Rect &r : rects) {
        if(check(P(r.left(), r.top()), rects, V, X, Y)
            || check(r.rt, rects, V, X, Y))
        {
            cout << "Yes" << endl;
            return true;
        }
    }
    cout << "No" << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
