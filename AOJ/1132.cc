#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>
#include <utility>

using namespace std;

typedef complex<double> Point;

bool eqv(double a, double b) {
    return abs(a-b) < 1e-5;
}

pair<double,double> key_point(double y, const Point &p) {
    double len = sqrt(1.0 - pow(y-p.imag(), 2));
    return make_pair(p.real()+len, p.real()-len);
}

bool inCircle(const Point &p, const Point &center, double radius) {
    double dist2 = norm(p-center);
    double rad2 = radius*radius;
    return dist2 < radius*radius || eqv(dist2, rad2);
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<Point> ps(N);
        vector<double> ys;
        for(int i = 0; i < N; ++i) {
            cin >> ps[i].real() >> ps[i].imag();
            ys.push_back(ps[i].imag()-1);
            ys.push_back(ps[i].imag()+1);
        }
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        int ans = 0;
        for(vector<double>::iterator it = ys.begin(); it != ys.end(); ++it) {
            double y = *it;
            for(vector<Point>::iterator pit = ps.begin(); pit != ps.end(); ++pit) {
                pair<double,double> key = key_point(y, *pit);
                for(int i = 0; i < 2; ++i) {
                    double x = i ? key.first : key.second;
                    Point center(x, y);
                    int cnt = 0;
                    for(vector<Point>::iterator pit2 = ps.begin(); pit2 != ps.end(); ++pit2) {
                        if(inCircle(*pit2, center, 1)) ++cnt;
                    }
                    ans = max(cnt, ans);
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
