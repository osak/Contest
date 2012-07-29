#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    int T;
    scanf("%d", &T);

    while(T--) {
        int N;
        scanf("%d", &N);

        int ans = 0;
        int minval = 0;
        for(int i = 0; i < N; ++i) {
            int v;
            scanf("%d", &v);
            if(i == 0) {
                minval = v;
            }
            else {
                minval = min(minval, v);
                int diff = v-minval;
                ans = max(ans, diff);
            }
        }

        if(ans == 0) {
            puts("UNFIT");
        }
        else {
            printf("%d\n", ans);
        }
    }

    return 0;
}

