#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int main() {
    int cases; 
    cin >> cases;

    for(int C = 1; C <= cases; ++C) {
        int L, P, F;
        cin >> L >> P >> F;

        int t = L;
        int step = 0;
        while(t < P) {
            t *= F*F;
            step++;
        }

        int ans = 0;
        while(step > 0) {
            ans++;
            step /= 2;
        }
        printf("Case #%d: %d\n", C, ans);
    }

    return 0;
}

