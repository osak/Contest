#include <iostream>
#include <vector>
#include <cstdio>
#include <complex>
#include <cmath>

using namespace std;

typedef complex<double> Point;

int main() {
    int cnt = 1;
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<Point> points;
        for(int i = 0; i < N; ++i) {
            Point p;
            cin >> p.real() >> p.imag();
            points.push_back(p);
        }

        double area = 0;
        for(int i = 0; i < N; ++i) {
            int next = (i+1) % N;
            area += points[i].real()*points[next].imag()-points[i].imag()*points[next].real();
        }
        printf("%d %.1f\n", cnt++, abs(area/2));
    }
    return 0;
}

