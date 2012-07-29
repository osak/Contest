#include <cstdio>

using namespace std;

int main() {
    int left = 1, right = 1000000001;
    for(int i = 0; i < 32; ++i) {
        int center = (left+right) / 2;
        printf("?%d\n", center);
        fflush(stdout);

        int ans;
        scanf("%d", &ans);
        if(ans == 0) break;
        else if(ans == 1) left = center+1;
        else right = center;
    }

    printf("!%d\n", (left+right)/2);
    fflush(stdout);

    return 0;
}
