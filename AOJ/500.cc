#include <iostream>

using namespace std;

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        int a = 0, b = 0;
        while(N--) {
            int i, j;
            cin >> i >> j;
            if(i > j) a += i+j;
            else if(i < j) b += i+j;
            else {
                a += i;
                b += j;
            }
        }
        cout << a << ' ' << b << endl;
    }
    return 0;
}

