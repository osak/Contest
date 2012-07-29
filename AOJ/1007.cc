#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main() {
    int C = 1;
    while(true) {
        int N;
        scanf("%d", &N);

        if(!N) break;

        vector<vector<int> > v(N, vector<int>(N, 0));

        int cnt = 1;
        for(int sum = 0; sum <= (N-1)*2; ++sum) {
            for(int y = 0; y <= min(sum, N-1); ++y) {
                int x = sum-y;
                if(0 <= x && x <= N-1) v[y][x] = cnt++;
            }
        }

        for(int sum = 0; sum <= (N-1)*2; ++sum) {
            if(sum & 1) continue;
            if(sum < N) {
                for(int y = max(0, sum-N); y <= min(sum, N-1)/2; ++y) {
                    int x = sum-y;
                    if(0 <= x && x <= N-1 && y < x) swap(v[y][x], v[x][y]);
                }
            }
            else {
                for(int x = N-1; x >= 0; --x) {
                    int y = sum-x;
                    if(0 <= y && y <= N-1 && x < y) swap(v[y][x], v[x][y]);
                }
            }
        }


        printf("Case %d:\n", C);
        for(int y = 0; y < N; ++y) {
            for(int x = 0; x < N; ++x) {
                printf("%3d", v[y][x]);
            }
            puts("");
        }
        ++C;
    }
    return 0;
}
