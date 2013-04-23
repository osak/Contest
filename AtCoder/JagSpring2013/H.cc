//Name: Rings
//Level: 4
//Category: 幾何
//Note:

/*
 * 片方の円周上の点を100万分割して，これらの点のうちもう片方の円の平面上に乗っているものに対して
 * 円内に入っているかを判定する．
 * このような点が1点のみであれば交差している．
 * ただし，誤差の関係で平面上判定が正確でないため，円内に入っている状態が連続している限りは1点とみなすようにしている．
 */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-5;

bool EQV(double a, double b) {
    return fabs(a-b) < EPS;
}

struct P3 {
    double x, y, z;

    P3() {}
    P3(double x, double y, double z) : x(x), y(y), z(z) {}

    P3& operator /=(double a) {
        x /= a;
        y /= a;
        z /= a;
        return *this;
    }

    P3 unit() const {
        P3 p = *this;
        p /= p.length();
        return p;
    }

    double dot(const P3 &other) const {
        return x*other.x + y*other.y + z*other.z;
    }

    P3 cross(const P3 &other) const {
        return P3(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
    }

    double norm() const {
        return x*x + y*y + z*z;
    }

    double length() const {
        return sqrt(norm());
    }
};

P3 operator +(const P3 &a, const P3 &b) {
    return P3(a.x+b.x, a.y+b.y, a.z+b.z);
}

P3 operator -(const P3 &a, const P3 &b) {
    return P3(a.x-b.x, a.y-b.y, a.z-b.z);
}

P3 operator *(double a, const P3 &b) {
    return P3(a*b.x, a*b.y, a*b.z);
}

istream& operator >> (istream &is, P3 &p3)  {
    return is >> p3.x >> p3.y >> p3.z;
}

ostream& operator << (ostream &os, const P3 &p3) {
    return os << "(" << p3.x << "," << p3.y << "," << p3.z << ")";
}

bool solve() {
    P3 c1, u1, v1, c2, u2, v2;
    cin >> c1 >> u1 >> v1 >> c2 >> u2 >> v2;

    u1 = u1.unit();
    v1 = v1.unit();
    u2 = u2.unit();
    v2 = v2.unit();
    c2 = c2 - c1;
    c1 = P3(0, 0, 0);
    // Check parallel
    const P3 perp1 = u1.cross(v1);
    const P3 perp2 = u2.cross(v2);
    if(EQV(fabs(perp1.dot(perp2)), perp1.norm()*perp2.norm())) {
        return false;
    }

    const int lim = 1000000;
    int in_c1 = 0;
    bool prev_in_c1 = false;
    for(int i = 0; i < lim; ++i) {
        const double angle = 2*PI*i / lim;
        const P3 c2p = c2 + cos(angle)*u2 + sin(angle)*v2;
        const P3 vec = c2p - c1;
        //if(i < lim*3/4) cout << c2p << ' ' << vec.dot(perp1) << endl;
        // Check if c2p is on u1-v1 plane
        if(EQV(vec.dot(perp1), 0)) {
            if(vec.length() <= 1 && !prev_in_c1) ++in_c1;
            prev_in_c1 = true;
        } else {
            prev_in_c1 = false;
        }
    }
    //cout << in_c1 << endl;
    return in_c1 == 1;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    if(solve()) cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}
