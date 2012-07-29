#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

bool eqv(double a, double b) {
    return fabs(a-b) < 1e-10;
}

struct Rect {
    double x, y, w, h;

    Rect() {}
    Rect(double x, double y, double w, double h) : x(x), y(y), w(w), h(h) {}

    bool intersect(const Rect &other) const {
        return (other.x < x+w) && (other.x+other.w > x) && (other.y < y+h) && (other.y+other.h > y);
    }

    bool include(double x_, double y_) const {
        return (x < x_ || eqv(x, x_)) && (x_ < x+w || eqv(x_, x+w)) && (y < y_ || eqv(y, y_)) && (y_ < y+h || eqv(y_, y+h));
    }

    bool include(const Rect &other) const {
        return (x < other.x || eqv(x, other.x)) && (x+w > other.x+other.w || eqv(x+w, other.x+other.w)) && (y < other.y || eqv(y, other.y)) && (y+h > other.y+other.h || eqv(y+h, other.y+other.h));
    }

    bool include_x(double x_) const {
        return x < x_ && x_ < x+w;
    }

    bool include_y(double y_) const {
        return y < y_ && y_ < y+h;
    }

    double area() const {
        return w*h;
    }
};

ostream& operator << (ostream &os, const Rect &r) {
    os << '(' << r.x << ',' << r.y << ',' << r.w << ',' << r.h << ')';
    return os;
}

int main() {
    for(int C = 1; ; ++C) {
        int N;
        cin >> N;
        if(!N) break;

        vector<Rect> v;
        while(N--) {
            double cx, cy, s;
            cin >> cx >> cy >> s;

            const Rect r(cx-s, cy-s, s*2, s*2);
            vector<Rect> next;
            for(int i = 0; i < v.size(); ++i) {
                if(r.include(v[i])) continue;

                Rect ri = v[i];
                if(!r.intersect(ri)) {
                    next.push_back(ri);
                }
                else {
                    if(ri.include_x(r.x)) {
                        const Rect cr(ri.x, ri.y, r.x-ri.x, ri.h);
                        next.push_back(cr);
                        ri = Rect(cr.x+cr.w, cr.y, ri.w-cr.w, cr.h);
                    }
                    if(ri.include_x(r.x+r.w)) {
                        const Rect cr(r.x+r.w, ri.y, ri.x+ri.w-(r.x+r.w), ri.h);
                        next.push_back(cr);
                        ri = Rect(ri.x, ri.y, ri.w-cr.w, ri.h);
                    }
                    if(ri.include_y(r.y)) {
                        const Rect cr(ri.x, ri.y, ri.w, r.y-ri.y);
                        next.push_back(cr);
                        ri = Rect(cr.x, cr.y+cr.h, cr.w, ri.h-cr.h);
                    }
                    if(ri.include_y(r.y+r.h)) {
                        const Rect cr(ri.x, r.y+r.h, ri.w, ri.y+ri.h-(r.y+r.h));
                        next.push_back(cr);
                        ri = Rect(ri.x, ri.y, ri.w, ri.h-cr.h);
                    }
                }
            }
            next.push_back(r);
            v = next;
        }
        
        double ans = 0;
        //cout << v.size() << endl;
        for(int i = 0; i < v.size(); ++i) {
            ans += v[i].area();
        }
        printf("%d %.2f\n", C, ans);
    }

    return 0;
}
