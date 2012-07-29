#include <iostream>

using namespace std;

int main() {
    int D;
    while(cin >> D) {
        int sum = 0;
        for(int i = D; i < 600; i += D) sum += i*i*D;
        cout << sum << endl;
    }
    return 0;
}

