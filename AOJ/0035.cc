//Name: Is It Convex?
//Level: 1
//Category: 幾何,外積
//Note:

/*
 * 外積の符号がずっと変化しなければ凸。
 */
#include <iostream>
#include <complex>
#include <sstream>
#include <string>

using namespace std;

typedef complex<double> Point;

//Verified PKU 2812
double cross(const Point &v1, const Point &v2) {
    return (v1.real()*v2.imag()) - (v1.imag()*v2.real());
}

//Verified AOJ 0012
bool ccw(const Point &p1, const Point &p2, const Point &p3) {
    return cross(p2-p1, p3-p1) < 0;
}

int main() {
    string line;
    while(cin >> line) {
        for(int i = 0; i < line.size(); ++i)
            if(line[i] == ',') line[i] = ' ';
        istringstream is(line);
        Point ps[4];
        for(int i = 0; i < 4; ++i) is >> ps[i].real() >> ps[i].imag();
        bool prev = ccw(ps[0], ps[1], ps[2]);
        bool ok = true;
        for(int i = 1; i < 4; ++i) {
            if(ccw(ps[i], ps[(i+1)%4], ps[(i+2)%4]) != prev) {
                ok = false;
                break;
            }
        }
        cout << (ok?"YES":"NO") << endl;
    }
    return 0;
}
