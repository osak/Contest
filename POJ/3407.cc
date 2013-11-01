//Name: Brookebond s'en va en guerre...
//Level: 2
//Category: 幾何,Geometry,3次元
//Note:

/**
 * 球面上の2点間の最短距離は、球と同じ中心をもち、与えられた2点を通る円弧の長さと等しい。
 * 緯度と経度から座標への変換は、まず緯度でxy平面上の円とz座標を確定させ、
 * それからx,y座標を求めれば良い。
 *
 * オーダーはO(1)。
 */
#include <cstdio>
#include <cmath>

using namespace std;

const double RADIUS = 6370;
const double PI = acos(-1.0);

void read_coord(double &x, double &y, double &z) {
    int lad, lam, lod, lom;
    char ladir, lodir;
    scanf("%d %d %c %d %d %c", &lad, &lam, &ladir, &lod, &lom, &lodir);
    double la = (lad + lam / 60.0) * PI / 180;
    if(ladir == 'S') {
        la = -la;
    }
    double lo = (lod + lom / 60.0) * PI / 180;
    if(lodir == 'W') {
        lo = -lo;
    }
    double eff_radius = RADIUS * cos(la);
    z = RADIUS * sin(la);
    x = eff_radius * cos(lo);
    y = eff_radius * sin(lo);
}

int main() {
    double x1, y1, z1;
    double x2, y2, z2;
    read_coord(x1, y1, z1);
    read_coord(x2, y2, z2);
    double angle = acos((x1*x2 + y1*y2 + z1*z2) / RADIUS / RADIUS);
    printf("%.3f\n", angle * RADIUS);
    return 0;
}
