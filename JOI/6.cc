#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>

using namespace std;

int dp[1<<21];

//Calc a**n mod m
int powmod(int a, int n, int m) {
    if(n < 0) abort();
    if(n == 0) return 1;
    if(n == 1) return a % m;
    return (powmod(a, n/2, m)*powmod(a, n-n/2, m)) % m;
}

int main() {
    int H, W;
    cin >> H >> W;

    vector<string> m(H);
    map<pair<int, int>, int> nonjoi;

    int rem_empty = 0;
    for(int i = 0; i < H; ++i) {
        cin >> m[i];
        for(int j = 0; j < W; ++j)
            if(m[i][j] == '?') ++rem_empty;
    }

    int ans = 0;
    int all = powmod(3, rem_empty, 100000);
    int nonjoi_sum = 0;
    int org_rem = rem_empty;
    for(int y = 0; y < H; ++y) {
        for(int x = 0; x < W; ++x) {
            //if(m[y][x] == '?') --rem_empty;
            if(x == W-1 || y == H-1) continue;

            if((m[y][x] == 'J' || m[y][x] == '?') &&
               (m[y][x+1] == 'O' || m[y][x+1] == '?') &&
               (m[y+1][x] == 'I' || m[y+1][x] == '?'))
            {
                int n = 0;
                //if(m[y][x] != '?') ++n;
                if(m[y][x+1] == '?') ++n;
                if(m[y+1][x] == '?') ++n;
                int cnt = (powmod(3, rem_empty-n, 100000))%100000;
                cout << cnt << " " << nonjoi_sum << endl;
                ans = (ans+((cnt%100000)*(nonjoi_sum+1))) % 100000;
                nonjoi_sum += nonjoi[make_pair(x, y)] = (powmod(3, org_rem-n, 100000) - cnt + 100000) % 100000;
                //cout << nonjoi_sum << endl;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
