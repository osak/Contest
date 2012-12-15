//Name: A Symmetric Point
//Level: 2
//Category: 幾何
//Note:

/*
 * Qから直線p1p2に下ろした垂線の足では，v = p2 - p1, vperp = v*(0,i) として
 *   p1 + αv = q + βvperp
 * が成立する．
 * v・vperp = 0 であることを利用して両辺に右からvperpをドット積で掛けることでβを求める．
 */
#include <cstdio>
#include <complex>
#include <cmath>

using namespace std;
typedef complex<double> Vector;

double dot(const Vector &v1, const Vector &v2) {
    return v1.real()*v2.real() + v1.imag()*v2.imag();
}

int main() {
    double X1, Y1, X2, Y2, XQ, YQ;
    while(scanf("%lf,%lf,%lf,%lf,%lf,%lf", &X1, &Y1, &X2, &Y2, &XQ, &YQ) != EOF) {
        const Vector p1(X1, Y1), p2(X2, Y2), q(XQ, YQ);
        const Vector l(p2-p1);
        const Vector perp(l * Vector(0, -1));
        const double beta = dot(p1 - q, perp) / norm(perp);
        const Vector r(q + perp * (beta * 2));
        printf("%.6f %.6f\n", r.real(), r.imag());
    }
    return 0;
}
