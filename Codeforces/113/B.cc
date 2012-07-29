#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>

using namespace std;

typedef complex<double> Point;

double cross(const Point &p1, const Point &p2) {
    return p1.real()*p2.imag() - p1.imag()*p2.real();
}

double ccw(const Point &p1, const Point &p2, const Point &p3) {
    return cross(p2-p1, p3-p1);
}

double dot(const Point &p1, const Point &p2) {
    return p1.real()*p2.real() + p1.imag()*p2.imag();
}

int main() {
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    vector<Point> a_tmp;
    for(int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        a_tmp.push_back(Point(x, y));
    }
    reverse(a_tmp.begin(), a_tmp.end());

    vector<Point> a;
    int rightmost = 0;
    for(int i = 0; i < N; ++i) {
        if(a_tmp[i].real() > a_tmp[rightmost].real()) {
            rightmost = i;
        }
    }
    for(int i = rightmost; i < N; ++i) a.push_back(a_tmp[i]);
    for(int i = 0; i < rightmost; ++i) a.push_back(a_tmp[i]);

    int M;
    cin >> M;
    bool ok = true;
    for(int i = 0; i < M && ok; ++i) {
        int x, y;
        cin >> x >> y;
        const Point p(x, y);

        int left = 1, right = N;
        while(left < right) {
            int center = (left+right) / 2;
            const Point &pt = a[center];
            double ccw_val = ccw(a[0], pt, p);
            if(abs(ccw_val) < 1e-9) {
                // ccw == 0
                if(center == 1 || center == N-1) {
                    ok = false;
                }
                else {
                    const Point p1 = p - a[0];
                    const Point p2 = pt - a[0];
                    ok = dot(p1, p2) > 0 && norm(p1) < norm(p2);
                }
                goto next;
            }

            if(ccw_val > 0) {
                left = center+1;
            }
            else if(ccw_val < 0) {
                right = center;
            }
        }
        if(left == N) {
            ok = false;
        }
        else {
            double val = ccw(a[left-1], a[left], p);
            if(abs(val) < 1e-9) val = 0;
            if(val <= 0) ok = false;
        }
next:
        ;
    }

    cout << (ok ? "YES" : "NO") << endl;

    return 0;
}
