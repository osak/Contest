//Name: Orthogonal
//Level: 1
//Category: 幾何,やるだけ
//Note:

/*
 * 内積が0になれば直交。
 */
#include <iostream>
#include <complex>

using namespace std;

typedef complex<double> Point;

double dot(const Point &v1, const Point &v2) {
    return v1.real()*v2.real() + v1.imag()*v2.imag();
}

int main() {
    while(true) {
        Point ps[4];
        for(int i = 0; i < 4; ++i) 
            cin >> ps[i].real() >> ps[i].imag();
        if(cin.eof()) break;

        if(dot(ps[0]-ps[1], ps[2]-ps[3]) == 0) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
