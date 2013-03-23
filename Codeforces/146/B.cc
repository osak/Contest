#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1000000;
int tbl[MAXN+1];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    for(int i = 1; i <= MAXN; ++i) {
        for(int j = i; j <= MAXN; j += i) {
            tbl[j]++;
        }
    }

    int a, b, c;
    cin >> a >> b >> c;
    int ans = 0;
    for(int i = 1; i <= a; ++i) {
        for(int j = 1; j <= b; ++j) {
            for(int k = 1; k <= c; ++k) {
                ans += tbl[i*j*k];
                ans %= 1<<30;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
