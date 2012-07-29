#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

double round_(double x) {
    if(abs((double)x) < 0.001) return 0;
    return x;
}

int main() {
    int a, b, c, d, e, f;
    while(cin >> a >> b >> c >> d >> e >> f) {
        int det = a*e - b*d;
        double x = (e*c - b*f) / (double)det;
        double y = (-d*c + a*f) / (double)det;
        printf("%.3f %.3f\n", round_(x), round_(y));
    }
    return 0;
}
