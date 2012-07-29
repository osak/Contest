#include <iostream>

using namespace std;

int main() {
    int sum = 0;
    for(int i = 0; i < 4; ++i) {
        int n;
        cin >> n;
        sum += n;
    }
    cout << sum / 60 << endl;
    cout << sum % 60 << endl;

    return 0;
}
