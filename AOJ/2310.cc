//Name: Rose Garden Witch
//Level: 3
//Category: 幾何
//Note:

/**
 * 走査線を0度から徐々に正の向きに回転させていく。
 * このとき、図形の角が必ず直角であることから、角の向き4通りについて、分割数が増えるか減るかが決定できる。
 * このような角を角度順にソートし、イベントドリブンで分割数を求めれば良い。
 *
 * オーダーはO(HW log HW)。
 */
#include <iostream>
#include <complex>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef complex<double> Vector;

const double EPS = 1e-9;

bool inRange(int a, int x, int b) {
    return a <= x && x < b;
}

char get(const vector<string> &f, int r, int c) {
    if(!inRange(0, r, f.size()) || !inRange(0, c, f[0].size())) return 0;
    return f[r][c] == '#';;
}

bool eqv(double a, double b) {
    return fabs(a-b) < EPS;
}

struct Point {
    double angle;
    bool inc;

    Point() {}
    Point(double a, bool i) : angle(a), inc(i) {}

    bool operator < (const Point &other) const {
        return angle < other.angle;
    }
};

int main() {
    int R, C;
    cin >> R >> C;

    vector<string> f(R);
    for(int i = 0; i < R; ++i) {
        cin >> f[i];
    }

    vector<Point> v;
    for(int r = -1; r < R; ++r) {
        for(int c = -1; c < C; ++c) {
            int pat = 0;
            pat |= get(f, r, c) << 3;
            pat |= get(f, r, c+1) << 2;
            pat |= get(f, r+1, c) << 1;
            pat |= get(f, r+1, c+1) << 0;

            if(pat == 0x1 || pat == 0xe) {
                double angle = atan2(R-r-1, c+1);
                v.push_back(Point(angle, false));
                //cout << r << ' ' << c << '(' << angle << ')' << " false" << endl;
            }
            else if(pat == 0x8 || pat == 0x7) {
                double angle = atan2(R-r-1, c+1);
                v.push_back(Point(angle, true));
                //cout << r << ' ' << c << '(' << angle << ')' << " true" << endl;
            }
        }
    }

    sort(v.begin(), v.end());

    int cnt = 1;
    int ans = 1;
    for(int i = 0; i < v.size(); ++i) {
        if(v[i].inc) ++cnt;
        else --cnt;
        if(i+1 < v.size() && eqv(v[i].angle, v[i+1].angle)) continue;

        //cout << "i=" << i << ' ' << cnt << endl;
        ans = max(ans, cnt);
    }

    cout << ans << endl;

    return 0;
}
