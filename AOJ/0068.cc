//Name: Enclose Pins with a Rubber Band
//Level: 2
//Category: 凸包
//Note:

/*
 * 凸包を求め，点の数から凸包を構成する点の数を引けばよい．
 */
#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>

using namespace std;

typedef complex<double> Point;

//Verified PKU 2812
double cross(const Point &v1, const Point &v2) {
    return (v1.real()*v2.imag()) - (v1.imag()*v2.real());
}

//Verified AOJ 0012
//Verified PKU 3348
double ccw(const Point &p1, const Point &p2, const Point &p3) {
    return cross(p2-p1, p3-p1);
}

//Verified PKU 3348
bool cmp(const Point &p1, const Point &p2) {
    return p1.real() < p2.real();
}

//Verified PKU 3348
vector<Point> convex_hull(const vector<Point> &points) {
    int N = points.size();
    vector<Point> v = points;
    sort(v.begin(), v.end(), cmp);
    vector<Point> hull(2*N);
    int pos = 0;
    for(int i = 0; i < N; ++i) {
        while(pos >= 2 && ccw(hull[pos-2], hull[pos-1], v[i]) <= 0) --pos;
        hull[pos++] = v[i];
    }
    int lim = pos;
    for(int i = N-2; i >= 0; --i) {
        while(pos >= lim+1 && ccw(hull[pos-2], hull[pos-1], v[i]) <= 0) --pos;
        hull[pos++] = v[i];
    }
    hull.erase(hull.begin()+pos-1, hull.end());
    return hull;
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;
        vector<Point> ps(N);
        char comma;
        for(int i = 0; i < N; ++i) cin >> ps[i].real() >> comma >> ps[i].imag();

        vector<Point> hull = convex_hull(ps);
        cout << N-hull.size() << endl;
    }
    return 0;
}
