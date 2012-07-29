//Name: The Oldest Site
//Level: 3
//Category: 幾何,ハッシュ,Hash
//Note:

/*
 * 柱2本を決めたとき，残り2本の位置は2通りに絞られる．
 * 座標をハッシュ化しておくことでO(1)で存在判定が可能．
 */
#include <iostream>
#include <vector>
#include <set>
#include <complex>

using namespace std;

typedef complex<int> Point;

inline int hash(int x, int y) {
    return x*5001 + y;
}

inline bool exist(const vector<bool> &v, int x, int y) {
    if(x < 0 || 5000 < x || y < 0 || 5000 < y) return false;
    return v[hash(x, y)];
}

int main() {
    while(true) {
        int n;
        cin >> n;
        if(!n) break;
        vector<Point> poles;
        vector<bool> v(5000*5001+5000, false);

        for(int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            v[hash(x, y)] = true;
            poles.push_back(Point(x, y));
        }

        int ans = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < i; ++j) {
                Point diff = poles[j] - poles[i];
                Point p1 = poles[i] + Point(diff.imag(), -diff.real());
                Point p2 = poles[i] + Point(-diff.imag(), diff.real());
                if(exist(v, p1.real(), p1.imag())) {
                    if(exist(v, p1.real()+diff.real(), p1.imag()+diff.imag())) {
                        ans = max(ans, norm(diff));
                    }
                }
                if(exist(v, p2.real(), p2.imag())) {
                    if(exist(v, p2.real()+diff.real(), p2.imag()+diff.imag())) {
                        ans = max(ans, norm(diff));
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
