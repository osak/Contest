//Name: Lunch
//Level: 1
//Category: やるだけ
//Note:
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int p1, p2, p3;
    cin >> p1 >> p2 >> p3;
    int j1, j2;
    cin >> j1 >> j2;

    int min_p = min(p1, min(p2, p3));
    int min_j = min(j1, j2);
    cout << min_p+min_j-50 << endl;
    return 0;
}
