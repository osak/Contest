//Name: Treasure Hunt II
//Level: 1
//Category: 幾何,やるだけ
//Note:

#include <iostream>
#include <complex>
#include <cstdio>

using namespace std;
typedef complex<double> Vector;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    while(true) {
        int N;
        cin >> N;
        if(N == -1) break;

        Vector pos(1, 0);
        N--;
        while(N--) {
            Vector v(-pos);
            v *= Vector(0, -1);
            const double len = abs(v);
            pos += v / len;
        }
        printf("%f\n%f\n", pos.real(), pos.imag());
    }
    return 0;
}
