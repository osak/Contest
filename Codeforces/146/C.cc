#include <iostream>
#include <algorithm>

using namespace std;

typedef unsigned long long ULL;

ULL gcd(ULL a, ULL b) {
    if(a < b) swap(a, b);
    while(b > 0) {
        ULL tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    ULL N;
    cin >> N;
    ULL ans = 0;
    if(N == 1) {
        ans = 1;
    } else if(N == 2) {
        ans = 2;
    } else {
        ans = N*(N-1)*(N-2) / gcd(N, N-2);
        ans = max(ans, (N-1)*(N-2)*(N-3) / gcd(N-1, N-3));
        for(ULL i = 1; i <= N; ++i) {
            ans = max(ans, N*(N-1)*i / gcd(N*(N-1), i));
        }
    }
    cout << ans << endl;
    return 0;
}
