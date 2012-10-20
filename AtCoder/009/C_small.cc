#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N, K;
    cin >> N >> K;
    vector<int> v(N);
    for(int i = 0; i < N; ++i) v[i] = i;
    int ans = 0;
    do {
        int cnt = 0;
        for(int i = 0; i < N; ++i) {
            if(v[i] != i) ++cnt;
        }
        if(cnt == K) ++ans;
    } while(next_permutation(v.begin(), v.end()));
    cout << ans << endl;
    return 0;
}
