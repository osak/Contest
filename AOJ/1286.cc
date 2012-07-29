#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int main() {
    while(true) {
        int N, M, K;
        cin >> N >> M >> K;
        if(!N && !M && !K) break;

        int patnum = 1;
        for(int i = 0; i < N; ++i) patnum *= M;

        int sum = 0;
        for(int i = 0; i < patnum; ++i) {
            int pat = i;
            int dice = 0;
            for(int j = 0; j < N; ++j) {
                int n = (pat % M) + 1;
                dice += n;
                pat /= M;
            }
            if(dice > K) sum += dice - K;
            else sum += 1;
        }

        printf("%.8f\n", (double)sum / patnum);
    }
    return 0;
}
