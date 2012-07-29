#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

inline bool inrange(int a, int n, int b) {
    return a<=n && n<=b;
}

int days[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
    vector<int> D(3), B(3);

    scanf("%d.%d.%d", &D[0], &D[1], &D[2]);
    scanf("%d.%d.%d", &B[0], &B[1], &B[2]);

    sort(B.begin(), B.end());

    do {
        if(B[2] < D[2] && inrange(1,B[1],12) && inrange(1,B[0],days[B[1]])) {
            if(B[1] == 2 && B[0] == 29 && B[2] % 4) continue;

            if(D[2]-B[2] > 18
                    || (D[2]-B[2] == 18
                        && (B[1] < D[1] 
                            || (B[1] == D[1] && B[0] <= D[0])))) {
                cout << "YES" << endl;
                exit(0);
            }
        }
    } while(next_permutation(B.begin(), B.end()));

    cout << "NO" << endl;

    return 0;
}
