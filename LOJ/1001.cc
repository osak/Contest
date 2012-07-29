#include <iostream>
#include <algorithm>

using namespace std;

int main(void) {
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;

        int a, b;
        a = min(10, n);
        b = n-a;
        cout << a << ' ' << b << endl;
    }
    return 0;
}
