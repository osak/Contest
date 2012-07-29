#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int a, b;
    while(cin >> a >> b && !cin.eof()) {
        if(b > a) swap(a, b);
        while(b) {
            int tmp = a % b;
            a = b;
            b = tmp;
        }
        cout << a << endl;
    }
    return 0;
}
