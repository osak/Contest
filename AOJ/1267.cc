#include <iostream>
#include <vector>
#include <complex>
#include <utility>
#include <cmath>
#include <cassert>

using namespace std;

typedef complex<double> Vector;
typedef pair<Vector,Vector> Line;

const double EPS = 1e-8;

double cross(const Vector &v1, const Vector &v2) {
    return v1.real()*v2.imag() - v1.imag()*v2.real();
}

double dot(const Vector &v1, const Vector &v2) {
    return v1.real()*v2.real() + v1.imag()*v2.imag();
}

int ccw(const Vector &p1, const Vector &p2, const Vector &p3) {
    Vector v1 = p2-p1;
    Vector v2 = p3-p1;
    double op = cross(v1, v2);
    if(op > 0) return 1;
    if(op < 0) return -1;
    if(dot(v1, v2)) return 2;
    if(norm(v1) < norm(v2)) return -2;
    return 0;
}

Vector crosspoint(const Line &l1, const Line &l2) {
    double a = cross(l1.second-l1.first, l2.second-l2.first);
    double b = cross(l1.second-l1.first, l1.second-l2.first);
    if(fabs(a) < EPS && fabs(b) < EPS) return l2.first;
    assert(fabs(a) >= EPS);
    return l2.first + b / a * (l2.second-l2.first);
}

vector<Vector> convex_cut(const vector<Vector> &v, const Line &l) {
    vector<Vector> res;
    for(int i = 0; i < v.size(); ++i) {
        Vector cur = v[i], next = v[(i+1)%v.size()];
        if(ccw(l.first, l.second, cur) != -1) res.push_back(cur);
        if(ccw(l.first, l.second, cur)*ccw(l.first, l.second, next) < 0) {
            res.push_back(crosspoint(Line(cur, next), l));
        }
    }

    return res;
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(N == 0) break;

        vector<Vector> v;
        for(int i = 0; i < N; ++i) {
            double x, y;
            cin >> x >> y;
            v.push_back(Vector(x, y));
        }

        vector<Vector> poly;
        poly.push_back(Vector(-20000, -20000));
        poly.push_back(Vector(20000, -20000));
        poly.push_back(Vector(20000, 20000));
        poly.push_back(Vector(-20000, 20000));
        for(int i = 0; i < N; ++i) {
            const Vector &p1 = v[i];
            const Vector &p2 = v[(i+1)%N];
            const Vector v = p2-p1;
            poly = convex_cut(poly, Line(p1-v*50000., p1+v*50000.));
            //for(int j = 0; j < poly.size(); ++j) cout << poly[j] << ' ';
            //cout << endl;
        }

        cout << ((poly.size() > 0) ? 1 : 0) << endl;
    }
    return 0;
}
