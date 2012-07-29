#include <iostream>

using namespace std;

int main() {
    int a, b;

    while(cin >> a >> b && !cin.eof()) {
        cout << a+b << endl;
    }
    return 0;
}
