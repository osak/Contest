#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    for(int CASE = 1; CASE <= T; ++CASE) {
        int a, b;
        cin >> a >> b;
        cout << "Case " << CASE << ": " << a+b << endl;
    }
    return 0;
}
