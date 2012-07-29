#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int a, b;
    while(cin >> a >> b) {
        unsigned long long p = (unsigned long long)a*b;
        int gcd = __gcd(a, b);
        cout << gcd << ' ' << p/gcd << endl;
    }
    return 0;
}
