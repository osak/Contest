#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int bitcount(unsigned n) {
    n = (n&0x55555555) + ((n&0xaaaaaaaa)>>1);
    n = (n&0x33333333) + ((n&0xcccccccc)>>2);
    n = (n&0x0f0f0f0f) + ((n&0xf0f0f0f0)>>4);
    n = (n&0x00ff00ff) + ((n&0xff00ff00)>>8);
    n = (n&0x0000ffff) + ((n&0xffff0000)>>16);
    return n;
}

int main() {
    while(true) {
        int C, R;
        cin >> R >> C;
        if(!C && !R) break;

        vector<unsigned> cols(C, 0);
        for(int i = 0; i < R; ++i) {
            for(int j = 0; j < C; ++j) {
                int n;
                scanf("%d", &n);
                cols[j] = (cols[j]<<1) | n;
            }
        }

        int ans = 0;
        for(int pat = 0; pat < (1<<R); ++pat) {
            int cnt = 0;
            for(int i = 0; i < C; ++i) {
                unsigned r = cols[i] ^ pat;
                int c = bitcount(r);
                cnt += max(c, R-c);
            }
            ans = max(ans, cnt);
        }
        cout << ans << endl;
    }
    return 0;
}
