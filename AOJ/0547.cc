#include <iostream>
#include <vector>

using namespace std;

int main() {
    while(true) {
        int W, H;
        cin >> W >> H;
        if(!W && !H) break;

        /*
         * 0: 直進して下から
         * 1: 直進して左から
         * 2: 曲がって下から
         * 3: 曲がって左から
         */
        vector<vector<vector<int> > > v(W, vector<vector<int> >(H, vector<int>(4, 0)));

        for(int x = 0; x < W; ++x)
            v[x][0][1] = 1;
        for(int y = 0; y < H; ++y)
            v[0][y][0] = 1;

        for(int x = 1; x < W; ++x) {
            for(int y = 1; y < H; ++y) {
                v[x][y][0] = (v[x][y-1][0] + v[x][y-1][2]) % 100000;
                v[x][y][1] = (v[x-1][y][1] + v[x-1][y][3]) % 100000;
                v[x][y][2] = v[x][y-1][1];
                v[x][y][3] = v[x-1][y][0];
            }
        }

        int sum = 0;
        for(int i = 0; i < 4; ++i)
            sum += v[W-1][H-1][i];

        cout << sum%100000 << endl;
    }
    return 0;
}
