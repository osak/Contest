#include <iostream>
#include <complex>
#include <cmath>

using namespace std;

typedef complex<double> Point;

int main() {
    Point pos(0, 0);
    Point unit(0, 1);
    while(true) {
        int r, a;
        char c;
        cin >> r >> c >> a;
        if(r == 0 && a == 0) break;

        pos += unit * (double)r;
        unit *= polar(1.0, -M_PI*a/180);
    }
    cout << (int)pos.real() << endl;
    cout << (int)pos.imag() << endl;
    return 0;
}
