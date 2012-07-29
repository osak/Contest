#include <iostream>
#include <complex>
#include <cmath>

using namespace std;

typedef complex<double> Point;

bool parallel(const Point &v1, const Point &v2) {
    return abs(v1.real()*v2.imag() - v1.imag()*v2.real()) < 1e-10;
}

int main() {
    int N;
    cin >> N;
    while(N--) {
        Point ps[4];
        for(int i = 0; i < 4; ++i) cin >> ps[i].real() >> ps[i].imag();
        Point v1 = ps[1]-ps[0], v2 = ps[3]-ps[2];

        if(parallel(v1, v2)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
