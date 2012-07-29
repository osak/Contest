#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#include <cmath>

using namespace std;

typedef complex<double> Vector;

struct Rect {
    double l, t, r, b;

    Rect() {}
    Rect(double l, double t, double r, double b) : l(l), t(t), r(r), b(b) {}
};

double V;

bool inRange(double a, double x, double b) {
    return a < x && x < b;
}

double calc_val(double x, double theta) {
    return -4.9*pow(x, 2)/V/V/pow(cos(theta), 2) + tan(center)*x;
}

double search_center(double k, double l, double r) {
    for(int i = 0; i < 30; ++i) {
        double center = (l+r) / 2;
        double val = -k * pow(cos(center), 3) / sin(center);
        if(val < 1) r = center;
        else l = center;
    }

    return (l+r) / 2;
}

double search_theta(double x, double y, double l, double r, bool lower) {
    for(int i = 0; i < 30; ++i) {
        double center = (l+r) / 2;
        double val = calc_val(x, center);
        if(lower) {
            if(val < y) l = center;
            else r = center;
        }
        else {
            if(val < y) r = center;
            else l = center;
        }
    }

    return (l+r) / 2;
}

bool check_hit(double theta, const Rect &r) {
    //left side
    double lval = calc_val(r.l, theta);
    if(inRange(r.b, lval, r.t)) return true;

    //right side
    double rval = calc_val(r.r, theta);
    if(inRange(r.b, rval, r.t)) return true;

    //top side
    double a = -4.9/V/V/pow(cos(theta), 2);
    double b = tan(theta);
    double c = -r.t
    double d = b*b - 4*a*c;
    if(d >= 0) {
        double lt = (-b - sqrt(d))/2/a;
        if(inRange(r.l, lt, r.r)) return true;
        double rt = (-b + sqrt(d))/2/a;
        if(inRange(r.l, rt, r.r)) return true;
    }

    //bottom side
    c = -r.b;
    d = b*b - 4*a*c;
    if(d >= 0) {
        double lb = (-b - sqrt(d))/2/a;
        if(inRange(r.l, lb, r.r)) return true;
        double rb = (-b + sqrt(d))/2/a;
        if(inRange(r.l, rb, r.r)) return true;
    }

    return false;
}

int main() {
    int N, X, Y;
    cin >> N >> X >> Y;

    vector<Rect> rects;
    for(int i = 0; i < N; ++i) {
        Rect r;
        cin >> r.l >> r.b >> r.r >> r.t;
        rects.push_back(r);
    }

    bool ok = true;
    for(int i = 0; i < N; ++i) {
        const Rect &r = rects[i];
        const Vector target(r.l, r.t);
        const double k = -9.8 * target.real() * / V / V;
        const double center = search_center(k, 0, M_PI/2);
    }

    cout << (ok ? "Yes" : "No") << endl;
    return 0;
}
