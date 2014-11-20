//Name: Calculation of Area
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>

using namespace std;

bool solve() {
    int a, b;
    cin >> a >> b;
    cout << a*b/3.305785 << endl;
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) ;
    return 0;
}
