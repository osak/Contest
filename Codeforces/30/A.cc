#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main() {
    int A, B, N;
    cin >> A >> B >> N;

    for(int i = 0; i < 2000; ++i) {
        int p = 1, np;
        for(int j = 0; j < N; ++j) p *= i;
        np = (N&1) ? -p : p;
        if(abs(A*p) > abs(B)) break;

        if(A*p == B) {
            cout << i << endl;
            exit(0);
        }
        if(A*np == B) {
            cout << -i << endl;
            exit(0);
        }
    }
    cout << "No solution" << endl;

    return 0;
}
