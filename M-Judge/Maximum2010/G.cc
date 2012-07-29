#include <iostream>

using namespace std;

typedef long long LL;

int main() {
    int T;
    cin >> T;

    while(T--) {
        LL M, X;
        cin >> M >> X;

        LL base = 1;
        for(LL i = 0; ; ++i) {
            base *= M;
            LL l = (base-1)/(M-1);

            for(LL j = 1; ; ++j) {
                LL cnt = l*j;
                if(cnt == X) {
                    cout << j*base/M << endl;
                    goto next;
                }
                else if(cnt > X) break;
            }
        }
next:
        ;
    }
    return 0;
}
