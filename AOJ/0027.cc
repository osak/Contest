#include <iostream>

using namespace std;

const int days[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const char *daynames[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

int main() {
    while(true) {
        int m, d;
        cin >> m >> d;
        if(!m && !d) break;

        int daycnt = 0;
        for(int i = 1; i < m; ++i) daycnt += days[i];
        daycnt += d;
        cout << daynames[(daycnt+2) % 7] << endl;
    }
    return 0;
}
