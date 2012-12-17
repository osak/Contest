//Name: Overlaps of Seals
//Level: 3
//Category: 幾何
//Note:

/*
 * 円が最も多く重なっている領域の境界を考えると，ある2つの円の交点が境界に存在していて
 * 重なりに関わっている円すべてがこの点を含んでいることが分かる．
 * これは十分条件でもあるため，そのような円の個数を数えればよい．
 */
#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

typedef complex<double> Vector;

struct Circle {
    Vector center;
    double r;

    pair<Vector,Vector> intersection(const Circle &c) const {
        const double d = abs(c.center - center);
        const double cos_ = (d*d + r*r - c.r*c.r) / (2*d);
        const double sin_ = sqrt(r*r - cos_*cos_);
        const Vector e = (c.center - center) / d;
        return make_pair(center + e*Vector(cos_, sin_), center + e*Vector(cos_, -sin_));
    }

    inline bool intersects(const Circle &c) const {
        return norm(center-c.center) <= pow(r+c.r, 2);
    }

    inline bool contains(const Circle &c) const {
        return abs(center-c.center)+c.r <= r;
    }

    inline bool contains(const Vector &v) const {
        return abs(center-v) <= r;
    }
};

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<Circle> circles(N);
        for(int i = 0; i < N; ++i) {
            double x, y;
            scanf("%lf,%lf", &x, &y);
            circles[i].center = Vector(x, y);
            circles[i].r = 1;
        }
        int ans = 1;
        for(int i = 0; i < N; ++i) {
            const Circle c1 = circles[i];
            for(int j = 0; j < i; ++j) {
                const Circle c2 = circles[j];
                if(!c1.intersects(c2)) continue;
                pair<Vector,Vector> vs = c1.intersection(c2);
                int cnt1 = 0, cnt2 = 0;
                for(int k = 0; k < N; ++k) {
                    if(i == k || j == k) continue;
                    if(circles[k].contains(vs.first)) ++cnt1;
                    if(circles[k].contains(vs.second)) ++cnt2;
                }
                ans = max(ans, max(cnt1, cnt2)+2);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
