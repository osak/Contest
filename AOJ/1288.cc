#include <iostream>
#include <algorithm>
#include <complex>
#include <utility>

typedef complex<int, int> Point;
typedef pair<Point, Point> Line;

bool on(const Point &p, const Line &l) {
    Point pv = p - l.first;
    Point lp = l.second - l.first;
    return norm(pv)*norm(lp) == pv.real()*lp.real() + pv.imag()*lp.imag();
}

int ccw(const Line &l1, const Line &l2) {
    Line v1 = l1.second - l1.first;
    Line v2 = l2.first - l2.second;
    return v1.real()*v2.imag() - v1.imag()*v2.real() > 0;
}

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<bool> exist(10, false);
        vector<Line> lines;
        vector<int> links(N*2, -1);
        vector<int> ons(N*2, -1);
        vector<int> on_rev(N, -1);

        for(int i = 0; i < N; ++i) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            lines.push_back(Line(Point(x1, y1), Point(x2, y2)));
        }

        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < i; ++j) {
                if(lines[i].first == lines[j].first) {
                    links[i*2] = j;
                    links[j*2] = i;
                }
                if(lines[i].first == lines[j].second) {
                    links[i*2] = j+1;
                    links[j*2+1] = i;
                }
                if(lines[i].second == lines[j].first) {
                    links[i*2+1] = j;
                    links[j*2] = i+1;
                }
                if(lines[i].second == lines[j].second) {
                    links[i*2+1] = j+1;
                    links[j*2+1] = i+1;
                }

                if(on(lines[i].first, lines[j])) {
                    ons[i*2] = j;
                    on_rev[j] = i*2;
                }
                if(on(lines[i].second, lines[j])) {
                    ons[i*2+1] = j;
                    on_rev[j] = i*2+1;
                }
                if(on(lines[j].first, lines[i])) {
                    ons[j*2] = i;
                    on_rev[i] = j*2;
                }
                if(on(lines[j].second, lines[i])) {
                    ons[j*2+1] = i;
                    on_rev[i] = j*2+1;
                }
            }
        }

        for(int i = 0; i < N*2; ++i) {
            if(links[i] == -1) {
                int pt = i/2 + (i==0);
                vector<int> hist;
                while(links[pt] != -1) {
                    hist.push_back(pt);
                    pt = links[pt];
                }
                int linkcnt = hist.size();
                if(linkcnt == 3) exist[9] = true;
                if(linkcnt == 1) exist[4] = true;
                if(linkcnt == 2) {
                    if(on_rev[hist[1]/2] != -1) exist[3] = true;
                    else exist[7] = true;
                }
                if(linkcnt == 0) {
                    if(on_rev[hist[0]/2] != -1) exist[4] = true;
                    else if(ons[hist[0]] != -1 && ons[hist[0]^1] != -1) exist[8] = true;
                    else if(ons[hist[0]^1] != -1) exist[3] = true;
                    else exist[1] = true;
                }
                if(linkcnt == 4) {
                    if(on_rev[hist[1]/2] != -1) exist[6] = true;
                    else if(ccw(Line(pt[0], pt[1]), Line(pt[1], pt[2]))) exist[5] = true;
                    else exist[2] = true;
                }
            }
        }
    }

    return 0;
}
