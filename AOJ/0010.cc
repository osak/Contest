//Name: Circumscribed Circle of a Triangle
//Level: 2
//Category: 幾何
//Note:

/*
 * 半径は正弦定理で求められる。
 * 中心座標は三平方の定理によって半径と辺の長さから求める。
 */
#include <iostream>
#include <cstdio>
#include <complex>
#include <cmath>

using namespace std;

typedef complex<double> Point;

bool eqv(double d1, double d2) {
    return abs(d1-d2) < 1e-10;
}

int main() {
    int N;

    cin >> N;
    while(N--) {
        double x1, x2, x3, y1, y2, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        Point p1(x1, y1), p2(x2, y2), p3(x3, y3);

        //正弦定理
        double R = abs(abs(p3-p2) / sin(arg(p2-p1) - arg(p3-p1))) / 2;

        //二等分点から中心までの距離を求める
        Point vb = p3-p2;
        double len = sqrt(R*R - norm(vb)/4.0);

        //垂線を生成する
        Point vbh = vb * Point(0, 1);
        Point center = p2 + vb/2.0 + vbh*len/abs(vbh);

        //これで求めた中心が外接円にならなければ、垂線ベクトルは逆方向
        if(eqv(abs(center-p1), R) && eqv(abs(center-p2), R) && eqv(abs(center-p3), R)) {}
        else center = p2 + vb/2.0 - vbh*len/abs(vbh);
        printf("%.3f %.3f %.3f\n", center.real(), center.imag(), R);
    }
    return 0;
}
