#include <iostream>
#include <vector>
#include <utility>

using namespace std;

typedef long long LL;
typedef pair<int, int> Point;

struct Matrix {
    int m[2][2];

    Matrix operator *(const Matrix &mm) {
        Matrix res;
        res.m[0][0] = m[0][0]*mm.m[0][0] + m[0][1]*mm.m[1][0];
        res.m[0][1] = m[0][0]*mm.m[0][1] + m[0][1]*mm.m[1][1];
        res.m[1][0] = m[1][0]*mm.m[0][0] + m[1][1]*mm.m[1][0];
        res.m[1][1] = m[1][0]*mm.m[0][1] + m[1][1]*mm.m[1][1];
        return res;
    }
};

int main() {
    LL n, j;
    cin >> n >> j;

    Point init;
    vector<Point> as;

    cin >> init.first >> init.second;
    LL sum_x = 0, sum_y = 0;
    for(int i = 0; i < n; ++i) {
        sum_x *= -1;
        sum_y *= -1;

        int x, y;
        cin >> x >> y;
        sum_x += 2*x;
        sum_y += 2*y;
        as.push_back(make_pair(x, y));
    }

    LL loopcnt = j / n;
    LL mod = j % n;
    LL coef_x = sum_x*(loopcnt&1), coef_y = sum_y*(loopcnt&1);
    for(int i = 0; i < mod; ++i) {
        coef_x *= -1;
        coef_y *= -1;
        coef_x += 2*as[i].first;
        coef_y += 2*as[i].second;
    }

    LL flg = (j&1) ? -1 : 1;
    cout << init.first*flg + coef_x << ' ' << init.second*flg + coef_y << endl;
    return 0;
}
