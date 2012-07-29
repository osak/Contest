#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    while(true) {
        int W, D;
        cin >> W >> D;
        if(!W && !D) break;

        int ans = 0;
        map<int,int> v1, v2;
        for(int i = 0; i < W; ++i) {
            int h;
            cin >> h;
            v1[h]++;
        }

        for(int i = 0; i < D; ++i) {
            int h;
            cin >> h;
            if(v1[h] > 0) {
                --v1[h];
            }
            ans += h;
        }

        for(map<int,int>::iterator it = v1.begin(); it != v1.end(); ++it) {
            ans += it->first * it->second;
        }

        cout << ans << endl;
    }
    return 0;
}
