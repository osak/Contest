#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> dp_all(1000001, 1000000);
    vector<int> dp_odd(1000001, 1000000);

    dp_all[0] = dp_odd[0] = 0;
    for(int i = 1; i <= 181; ++i) {
        int n = i*(i+1)*(i+2)/6;
        for(int j = 0; j+n <= 1000000; ++j) {
            dp_all[j+n] = min(dp_all[j+n], dp_all[j] + 1);
            if(n % 2 == 1) dp_odd[j+n] = min(dp_odd[j+n], dp_odd[j] + 1);
        }
    }

    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        cout << dp_all[N] << ' ' << dp_odd[N] << endl;
    }
    return 0;
}
