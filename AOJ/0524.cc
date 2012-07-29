#include <iostream>
#include <vector>
#include <set>
#include <complex>

using namespace std;

typedef complex<int> Point;

namespace std {
    bool operator < (const Point &p1, const Point &p2) {
        if(p1.real() != p2.real()) return p1.real() < p2.real();
        return p1.imag() < p2.imag();
    }
};

int main() {
    while(true) {
        int m;
        cin >> m;
        if(!m) break;

        vector<Point> targets;
        set<Point> stars;

        for(int i = 0; i < m; ++i) {
            int x, y;
            cin >> x >> y;
            targets.push_back(Point(x, y));
        }

        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            stars.insert(Point(x, y));
        }

        for(int i = 0; i < m; ++i) {
            for(set<Point>::iterator it = stars.begin(); it != stars.end(); ++it) {
                Point diff = *it - targets[i];
                bool ok = true;
                for(int j = 0; j < m; ++j) {
                    if(stars.find(targets[j]+diff) == stars.end()) {
                        ok = false;
                        break;
                    }
                }
                if(ok) {
                    cout << diff.real() << ' ' << diff.imag() << endl;
                    goto end;
                }
            }
        }
end:
        ;
    }
    return 0;
}
