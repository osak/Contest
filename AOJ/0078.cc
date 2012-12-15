//Name: Magic Square
//Level: 1
//Category: シミュレーション,やるだけ
//Note:

#include <cstdio>

using namespace std;

int main() {
    while(true) {
        int N;
        scanf("%d", &N);
        if(!N) break;
        int field[N][N];
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                field[i][j] = -1;
            }
        }
        int r = N/2 + 1, c = N/2;
        field[r][c] = 1;
        for(int num = 2; num <= N*N; ++num) {
            ++r;
            ++c;
            while(!(0 <= r && r < N && 0 <= c && c < N && field[r][c] == -1)) {
                if(c >= N) c = 0;
                if(c < 0) c = N-1;
                if(r >= N) r = 0;
                if(0 <= r && r < N && 0 <= c && c < N && field[r][c] != -1) {
                    ++r;
                    --c;
                }
            }
            field[r][c] = num;
        }
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                printf("%4d", field[i][j]);
            }
            puts("");
        }
    }
    return 0;
}
