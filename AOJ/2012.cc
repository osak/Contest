//Name: Space Coconut Crab
//Level: 2
//Category: 数学,探索
//Note: 

/**
 * zの範囲は0≦z≦E^(1/3)、yの範囲は0≦y≦E^(1/2)で表される。
 * zとyが決まればxも一意に決まるので、zとyを全探索し、x,y,z≧0を満たすような組み合わせについてx+y+zの最小値を求めればよい。
 *
 * オーダーは O(E^(5/6))。
 */
#include <iostream>
#include <algorithm>

using namespace std;

bool solve(bool first) {
    int E;
    if(!(cin >> E)) return false;
    if(!E) return false;

    int ans = E;
    for(int z = 0; z*z*z <= E; ++z) {
        for(int y = 0; y*y <= E; ++y) {
            const int x = E - z*z*z - y*y;
            if(x >= 0) {
                ans = min(ans, x+y+z);
            }
        }
    }
    cout << ans << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
