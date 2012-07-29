#include <iostream>
#include <vector>

using namespace std;

int main() {
    while(true) {
        int H, W, N;
        cin >> H >> W >> N;
        if(!H && !W && !N) break;

        vector<vector<int> > v(H, vector<int>(W));
        vector<vector<int> > cnt(H+1, vector<int>(W+1, 0));
        for(int i = 0; i < H; ++i) {
            for(int j = 0; j < W; ++j) {
                cin >> v[i][j];
            }
        }
        cnt[0][0] = N-1;
        for(int i = 0; i < H; ++i) {
            for(int j = 0; j < W; ++j) {
                cnt[i+1][j] += cnt[i][j]/2;
                cnt[i][j+1] += cnt[i][j]/2;
                if(cnt[i][j] & 1) {
                    if(v[i][j] == 0) cnt[i+1][j]++;
                    else cnt[i][j+1]++;

                    v[i][j] ^= 1;
                }
            }
        }
        int i = 0, j = 0;
        while(i < H && j < W) {
            if(v[i][j] == 0) ++i;
            else ++j;
        }
        cout << (i+1) << ' ' << (j+1) << endl;
    }
    return 0;
}
