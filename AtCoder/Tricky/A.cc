#include <cstdio>

using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        long long a, b;
        scanf("%lld %lld", &a, &b);
        if(a == (long long)(1ULL<<63) && b == -1) {
            puts("9223372036854775808");
        } else {
            printf("%lld\n", a/b);
        }
    }
    return 0;
}
