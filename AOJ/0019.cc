#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;
    long long ans = 1;
    for(int i = 1; i <= N; ++i) ans *= i;
    cout << ans << endl;
    return 0;
}
