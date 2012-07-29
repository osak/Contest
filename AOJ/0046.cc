//Name: Differential
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    double h;
    double maxval = 0, minval = 1e30;
    while(cin >> h) {
        maxval = max(h, maxval);
        minval = min(h, minval);
    }
    cout << maxval-minval << endl;
    return 0;
}
