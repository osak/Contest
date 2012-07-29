//Name: Class
//Level: 1
//Category: lower_bound,やるだけ
//Note:

#include <iostream>
#include <algorithm>

using namespace std;

double table[] = {0, 48, 51, 54, 57, 60, 64, 69, 75, 81, 91};
const char *cls[] = {"light fly", "fly", "bantam", "feather", "light", "light welter", "welter", "light middle", "middle", "light heavy", "heavy"};

int main() {
    double w;
    while(cin >> w) {
        double *pos = lower_bound(table, table+sizeof(table)/sizeof(double), w);
        cout << cls[pos-table-1] << endl;
    }
    return 0;
}
