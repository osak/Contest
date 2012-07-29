#include <iostream>
#include <complex>
#include <vector>
#include <utility>

using namespace std;

typedef complex<double> Point;
typedef pair<Point,Point> Line;

//Verified PKU 2812
double cross(const Point &v1, const Point &v2) {
    return (v1.real()*v2.imag()) - (v1.imag()*v2.real());
}

bool intersect(const Point &p11, const Point &p12, const Point &p21, const Point &p22) {
    return (cross(p12-p11, p21-p11)*cross(p12-p11, p22-p11) < 0 &&
            cross(p22-p21, p11-p21)*cross(p22-p21, p12-p21) < 0 );
}

//Verified AOJ 0012
//Verified PKU 3348
double ccw(const Point &p1, const Point &p2, const Point &p3) {
    return cross(p2-p1, p3-p1);
}

//Verified PKU 2812
double area(const vector<Point> &points) {
    double res = 0;
    for(int i = 0; i < points.size(); ++i) {
        int next = (i+1) % points.size();
        res += cross(points[i], points[next]);
    }
    return abs(res/2);
}

int main() {
    while(true) {
        int N, M, W, H, S;
        cin >> N >> M >> W >> H >> S;
        if(!N && !M && !W && !H && !S) break;

        vector<Line> ls;
        for(int i = 0; i < M; ++i) {
            Point p1, p2;
            cin >> p1.imag() >> p2.imag();
            p1.real() = 0;
            p2.real() = W;
            ls.push_back(Line(p1, p2));
        }

        vector<int> almonds(M+1, 0);
        for(int i = 0; i < N; ++i) {
            Point p;
            cin >> p.real() >> p.imag();

            int pos = M;
            for(int j = 0; j < M-1; ++j) {
                if(ccw(ls[j].first, ls[j].second, p) > 0 && ccw(ls[j+1].first, ls[j+1].second, p) < 0) {
                    pos = j;
                    break;
                }
            }
            almonds[pos]++;
        }

        vector<double> areas(M+1);
        for(int i = -1; i < M; ++i) {
            vector<Point> v;
            v.push_back(i==-1 ? Point(0, 0) : ls[i].first);
            v.push_back(i==-1 ? Point(W, 0) : ls[i].second);
            v.push_back(i==M ? Point(0, H) : ls[i+1].second);
            v.push_back(i==M ? Point(W, H) : ls[i+1].first);
            areas[i+1] = area(v);
        }

        int target = W*H-S;
        int left = -1;
        int cnt = 0;
        int s = 0;
        int ans = N;
        for(int i = 0; i < M+1; ++i) {
            s += areas[i];
            cnt += almonds[i];
            if(i == 0) left = 0;
            while(left <= i && s > target) {
                s -= areas[left];
                cnt -= almonds[left];
                left++;
            }

            if(s <= target) ans = min(ans, N-cnt);
        }
        cout << ans << endl;
    }
    return 0;
}
