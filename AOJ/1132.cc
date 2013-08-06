//Name: Circle and Points
//Level: 3
//Category: 幾何,円
//Note:

/*
 * 半径が固定なので，円周上に2点が乗っているときが境界状態．
 * すべての2点の組み合わせについて中心の来る場所（2点）を求め，内包判定を行う．
 * N=1のケースと，全ての点が互いに距離2以上離れているケースに注意．
 *
 * オーダーは O(N^3)．
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>
#include <utility>

using namespace std;

typedef complex<double> Point;

bool inCircle(const Point &p, const Point &center, double radius) {
    double dist2 = norm(p-center);
    double rad2 = radius*radius;
    return dist2 < rad2+1e-9;
}

int check(const Point &center, const vector<Point> &points) {
    const int N = points.size();
    int cnt = 0;
    for(int i = 0; i < N; ++i) {
        if(inCircle(points[i], center, 1)) ++cnt;
    }
    return cnt;
}

int test(int a, int b, const vector<Point> &points) {
    const Point v(points[a]-points[b]);
    if(abs(v) >= 2) return 1;
    const double hlen = abs(v)/2;

    const double plen = sqrt(1 - hlen*hlen);
    Point perp = v*Point(0, 1);
    perp /= abs(perp);
    const Point mid = (points[a]+points[b]) / 2.0;
    return max(check(mid + perp*plen, points), check(mid - perp*plen, points));
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<Point> points(N);
        for(int i = 0; i < N; ++i) {
            cin >> points[i].real() >> points[i].imag();
        }
        int ans = 0;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < i; ++j) {
                ans = max(ans, test(i, j, points));
            }
        }
        if(N == 1) ans = 1;
        cout << ans << endl;
    }
    return 0;
}
