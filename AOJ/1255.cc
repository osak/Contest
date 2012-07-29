#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <cassert>

using namespace std;

typedef complex<double> Vector;

struct Sphere {
    double x, y, z, r;

    Sphere() {}
};

enum Event {
    EVENT_START,
    EVENT_CROSS_START,
    EVENT_CROSS_END,
    EVENT_END,
};

struct Tag {
    Event evt;
    int s1, s2;
    double z;

    Tag() {}
    Tag(Event e, double z, int s) : evt(e), z(z), s1(s) {}
    Tag(Event e, double z, int s1, int s2) : evt(e), z(z), s1(s1), s2(s2) {}

    bool operator < (const Tag &other) const {
        return z < other.z;
    }
};

inline bool eqv(double a, double b) {
    return fabs(a-b) < 1e-8;
}

bool contains(const Sphere &s1, const Sphere &s2) {
    double d = sqrt(pow(s1.x-s2.x,2) + pow(s1.y-s2.y,2) + pow(s1.z-s2.z,2));
    return d < s1.r-s2.r;
}

double binsearch(const Sphere &s1, const Sphere &s2, double l, double r, int phase) {
    const double dist = sqrt(pow(s1.x-s2.x,2) + pow(s1.y-s2.y,2));
    for(int i = 0; i < 32; ++i) {
        const double mid = (l+r) / 2;
        const double r1 = sqrt(pow(s1.r,2) + pow(s1.z-mid,2));
        const double r2 = sqrt(pow(s2.r,2) + pow(s2.z-mid,2));
        if(r1+r2 > dist) {
            if(phase == 0) l = mid;
            else r = mid;
        }
        else {
            if(phase == 0) r = mid;
            else l = mid;
        }
    }

    return (l+r)/2;
}

void visit(const vector<vector<int> > &v, vector<int> &valid, int pos) {
    int N = v.size();
    for(int i = 0; i < N; ++i) {
        if(valid[i] && v[pos][i]) {
            valid[i] = false;
            visit(v, valid, i);
        }
    }
}

int dfs(const vector<vector<int> > &v, const vector<int> &valid) {
    int N = v.size();
    int res = 0;
    vector<int> valid_ = valid;
    for(int i = 0; i < N; ++i) {
        if(valid[i]) {
            ++res;
            visit(v, valid_, i);
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(0);
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        vector<Tag> events;
        vector<Sphere> spheres(N);
        vector<int> to_erase;
        for(int i = 0; i < N; ++i) {
            Sphere &s = spheres[i];
            cin >> s.x >> s.y >> s.z >> s.r;
            for(int j = 0; j < i; ++j) {
                if(contains(s, spheres[j])) {
                    to_erase.push_back(j);
                }
                else if(contains(spheres[j], s)) {
                    to_erase.push_back(i);
                    break;
                }
            }
            //events.push_back(Tag(EVENT_START, s.z - s.r, i));
            //events.push_back(Tag(EVENT_END, s.z + s.r, i));
        }
        for(int j = (int)to_erase.size()-1; j >= 0; --j) {
            spheres.erase(spheres.begin()+j);
        }

        N = spheres.size();
        for(int i = 0; i < N; ++i) {
            const Sphere &s1 = spheres[i];
            for(int j = i+1; j < N; ++j) {
                const Sphere &s2 = spheres[j];

                const double dist = sqrt(pow(s1.x-s2.x,2) + pow(s1.y-s2.y,2));
                if(dist > s1.r + s2.r) continue;

                double d = s1.r+s2.r - dist;
                double cz = s1.z + (s2.z-s1.z) * (s1.r-d/2) / d;
                double z1 = binsearch(s1, s2, max(s1.z-s1.r, s2.z-s2.r), cz, 0);
                double z2 = binsearch(s1, s2, cz, min(s1.z+s1.z, s2.z+s2.z), 1);
                events.push_back(Tag(EVENT_CROSS_START, z1, i, j));
                events.push_back(Tag(EVENT_CROSS_END, z2, i, j));
            }
            events.push_back(Tag(EVENT_START, s1.z-s1.r, i));
            events.push_back(Tag(EVENT_END, s1.z+s1.r, i));
        }

        int prev = 0;
        string ans = "";
        vector<int> valid(N, 0);
        vector<vector<int> > v(N, vector<int>(N, 0));
        sort(events.begin(), events.end());
        for(int i = 0; i < events.size(); ++i) {
            const Tag &t = events[i];
            switch(t.evt) {
                case EVENT_START:
                    valid[t.s1] = 1;
                    break;
                case EVENT_END:
                    valid[t.s1] = 0;
                    break;
                case EVENT_CROSS_START:
                    v[t.s1][t.s2] = v[t.s2][t.s1] = 1;
                    break;
                case EVENT_CROSS_END:
                    v[t.s1][t.s2] = v[t.s2][t.s1] = 0;
            }
            cout << "event " << t.evt << "at " << t.z << endl;

            if(i+1 < events.size() && eqv(t.z, events[i+1].z)) continue;
            int cnt = dfs(v, valid);
            if(cnt < prev) ans += "0";
            else if(cnt > prev) ans += "1";
            prev = cnt;
        }
        cout << ans.size() << endl << ans << endl;
    }
}
