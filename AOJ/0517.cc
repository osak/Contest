//Name: Longest Steps
//Level: 2
//Category: 尺取法,しゃくとり法
//Note:

/*
 * 連続した整数のかたまりに分割して考える．
 * 白紙は距離1だけ離れたふたつのかたまりを結合することができる．
 */
#include <iostream>
#include <vector>

using namespace std;

int main() {
    while(true) {
        int n, k;
        cin >> n >> k;
        if(!n && !k) break;
        vector<bool> v(n+1, false);

        bool wildcard = false;
        for(int i = 0; i < k; ++i) {
            int num;
            cin >> num;
            v[num] = true;
            if(num == 0) wildcard = true;
        }

        int prevlen = 0;
        int currlen = 0;
        int ans = 0;
        int i = 1;
        while(i <= n) {
            while(!v[i] && i <= n) ++i;
            if(i >= n+1) break;
            while(v[i++]) ++currlen;
            if(wildcard) {
                ans = max(ans, prevlen+currlen+1);
                if(i+1 <= n && v[i+1]) prevlen = currlen;
                else prevlen = 0;
            }
            else {
                ans = max(ans, currlen);
            }
            currlen = 0;
        }

        cout << ans << endl;
    }
    return 0;
}
