#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;

    vector<int> rev3(N+1, 0), ans(N, 0);
    for(int i = 0; i < N; ++i) {
        int a;
        cin >> a;
        rev3[a] = i+1;
    }
    for(int i = 0; i < N; ++i) {
        int a;
        cin >> a;
        ans[i] = rev3[a];
    }
    for(int i = 0; i < N; ++i) {
        if(i > 0) cout << ' ';
        cout << ans[i];
    }
    cout << endl;

    return 0;
}
