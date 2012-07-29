#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    string str;
    cin >> str;

    const int N = str.size();
    vector<int> lower_left(N, 0), upper_right(N, 0);
    for(int i = 0; i < N; ++i) {
        if(i > 0) lower_left[i] = lower_left[i-1];
        if(islower(str[i])) ++lower_left[i];
    }
    for(int i = N-1; i >= 0; --i) {
        if(i < N-1) upper_right[i] = upper_right[i+1];
        if(isupper(str[i])) ++upper_right[i];
    }

    int ans = N;
    for(int i = 0; i <= N; ++i) {
        int l = i>0 ? lower_left[i-1] : 0;
        int r = i<N ? upper_right[i] : 0;
        ans = min(ans, l+r);
    }

    cout << ans << endl;

    return 0;
}
