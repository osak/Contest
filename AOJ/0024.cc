#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double vt;
    while(cin >> vt) {
        double t = vt / 9.8;
        double h = 4.9 * t*t;
        cout << ceil((h+5)/5) << endl;
    }
    return 0;
}
