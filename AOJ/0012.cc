#include <iostream>
#include <complex>

using namespace std;

typedef complex<double> Point;

double prod(const Point &v1, const Point &v2) {
    return v1.real()*v2.imag() - v2.real()*v1.imag();
}

bool ccw(const Point &p1, const Point &p2, const Point &p3) {
    return prod(p2-p1, p3-p1) < 0;
}

int main() {
    double x1, y1, x2, y2, x3, y3, xp, yp;
    while(cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> xp >> yp) {
        Point p1(x1, y1), p2(x2, y2), p3(x3, y3), pp(xp, yp);
        bool f1 = ccw(p1, p2, pp), f2 = ccw(p2, p3, pp), f3 = ccw(p3, p1, pp);
        if(f1 == f2 && f2 == f3) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
