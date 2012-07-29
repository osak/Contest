//Name: Sequence
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>

using namespace std;

int main() {
    double a;
    cout.precision(10);
    cout.setf(ios::fixed, ios::floatfield);
    while(cin >> a) {
        double sum = 0;
        for(int i = 1; i <= 10; ++i) {
            sum += a;
            if(i % 2 == 0) a /= 3;
            else a *= 2;
        }
        cout << sum << endl;
    }
    return 0;
}
