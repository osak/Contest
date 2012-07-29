#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    int ans = 0;
    while(N--) {
        int cnt = 0;
        for(int i = 0; i < M; ++i) {
            int f;
            cin >> f;
            cnt += f;
        }
        ans = max(ans, cnt);
    }
    cout << ans << endl;
    return 0;
}
