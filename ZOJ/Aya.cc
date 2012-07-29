#include <iostream>

using namespace std;

int main() {
    int N;
    while(cin >> N) {
        long long ans = 0;
        if(N == 1) ans = 0;
        else if(N == 2) ans = 1;
        else {
            ans = 1;
            for(int i = 3; i <= N; ++i) {
                ans += i/2;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
