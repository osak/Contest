//Name: Third Root
//Level: 1
//Category: シミュレーション,やるだけ
//Note:

#include <cstdio>
#include <cmath>

using namespace std;

int main() {
    while(true) {
        int Q;
        scanf("%d", &Q);
        if(Q == -1) break;
        double limit = 0.00001 * Q;
        double ans = Q/2;
        while(fabs(ans*ans*ans - Q) >= limit) {
            ans = ans - (ans*ans*ans - Q) / (3*ans*ans);
        }
        printf("%f\n", ans);
    }
    return 0;
}
