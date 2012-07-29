#include <iostream>

using namespace std;

int main() {
    while(true) {
        int L;
        cin >> L;
        if(!L) break;

        int amt = 0;
        int ans = 0;
        for(int i = 0; i < 12; ++i) {
            int M, N;
            cin >> M >> N;
            amt += M-N;
            if(ans == 0 && amt >= L) ans = i+1;
        }
        if(ans > 0) cout << ans << endl;
        else cout << "NA" << endl;
    }
    return 0;
}
