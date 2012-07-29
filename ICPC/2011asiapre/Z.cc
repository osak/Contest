#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int main() {
    freopen("Z.txt", "r", stdin);
    while(true) {
        int A, B;
        scanf("%d %d", &A, &B);
        if(!A && !B) break;

        printf("%.9f\n", (double)(A+B)/2 - sqrt(A*B));
    }
    return 0;
}
