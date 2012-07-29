#include <iostream>

using namespace std;

int main() {
    while(true) {
        int sum;
        cin >> sum;
        if(!sum) break;
        for(int i = 0; i < 9; ++i) {
            int n;
            cin >> n;
            sum -= n;
        }
        cout << sum << endl;
    }
    return 0;
}
