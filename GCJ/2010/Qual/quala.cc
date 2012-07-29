#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    int cases;
    cin >> cases;
    for(int C = 1; C <= cases; ++C) {
        int N, K;
        cin >> N >> K;
        int pats = 1 << N;
        int mod = K % pats;
        printf("Case #%d: %s\n", C, (mod == pats-1) ? "ON" : "OFF");
    }
    return 0;
}
