#include <cstdio>
#include <vector>
#include <complex>
#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

typedef complex<double> Vector;
typedef pair<Vector, double> Circle;

bool eqv(double a, double b) {
    return abs(a-b) < 1e-7;
}

inline void update(double &a, double b) {
    if(a < b) a = b;
}

struct Range {
    double start, end;

    Range() {}
    Range(double s, double e) {
        start = max(s, 0.0);
        end = min(e, M_PI);
    }

    bool valid() const { return start < end; }

    double area() const { return end - start; }

    double includes(const Range &other) const {
        return (start < other.start || eqv(start, other.start)) && (other.end <= end || eqv(end, other.end));
    }

    bool cross_with(const Range &other) const {
        return (other.start < end) && (other.end > start);
    }

    bool merge(const Range &other) {
        if(!cross_with(other)) return false;

        start = min(start, other.start);
        end = max(end, other.end);
        return true;
    }

    bool operator < (const Range &other) const {
        return start < other.start;
    }

    bool operator == (const Range &other) const {
        return eqv(start, other.start) && eqv(end, other.end);
    }

    bool operator != (const Range &other) const {
        return !(*this == other);
    }
};

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    vector<Range> v;
    for(int i = 0; i < N; ++i) {
        int x, y, r;
        scanf("%d %d %d", &x, &y, &r);

        const Vector center = Vector(x, y);
        const double c_arg = arg(center);
        const double len = abs(center);
        Range range;
        if(len-r < 0 || eqv(len-r, 0)) {
            range = Range(0, M_PI);
        }
        else {
            const double theta = abs(asin(r / len));
            double s = c_arg-theta;
            double e = c_arg+theta;
            if(s < -M_PI) {
                s += 2*M_PI;
                e += 2*M_PI;
            }
            range = Range(s, e);
        }
        if(range.valid() && Range(0, M_PI).includes(range)) {
            v.push_back(range);
        }
    }
    {
        vector<Range> tmp;
        for(int i = 0; i < v.size(); ++i) {
            bool ok = true;
            for(int j = 0; j < v.size(); ++j) {
                if(v[j] != v[i] && v[j].includes(v[i])) ok = false;
            }
            if(ok) tmp.push_back(v[i]);
        }
        v = tmp;
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    //交差しているものの中で一番番号が小さいもの
    vector<int> prev(v.size(), 0);
    for(int i = 0; i < v.size(); ++i) {
        prev[i] = i;
        for(int j = 0; j < i; ++j) {
            if(v[i].cross_with(v[j])) {
                prev[i] = j;
                break;
            }
        }
    }

    vector<vector<double> > dp_use(v.size(), vector<double>(K+1, 0));
    vector<vector<double> > dp_nouse(v.size(), vector<double>(K+1, 0));
    double ans = 0;
    for(int k = 1; k <= K; ++k) {
        for(int i = 0; i < v.size(); ++i) {
            dp_use[i][k] = v[i].area();
            if(prev[i] != i) update(dp_use[i][k], dp_use[prev[i]][k-1] + v[i].end-max(v[i].start, v[prev[i]].end));
            if(prev[i] != 0) update(dp_use[i][k], dp_nouse[prev[i]-1][k-1] + v[i].area());

            update(dp_nouse[i][k], dp_use[i][k]);
            if(i > 0) update(dp_nouse[i][k], dp_nouse[i-1][k]);
            update(ans, dp_use[i][k]);
        }
    }

    printf("%.7f\n", ans / M_PI);
    
    return 0;
}
