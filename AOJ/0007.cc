#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int debt = 100; // *1000
    while(n--) {
        int r = debt % 20;
        debt += debt/20;
        if(r) ++debt;
    }
    cout << debt << "000" << endl;

    return 0;
}
