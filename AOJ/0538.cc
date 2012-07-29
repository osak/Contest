#include <iostream>
#include <string>

using namespace std;

int main() {
    while(true) {
        int N, M;
        string str;
        cin >> N;
        if(!N) break;
        cin >> M >> str;

        int ans = 0;
        int p = 0;
        int phase = 0;
        for(int i = 0; i < str.size(); ++i) {
            if(phase == 0) {
                if(str[i] == 'I') {
                    if(p >= N) ++ans;
                    phase = 1;
                }
                else p = 0;
            }
            else {
                if(str[i] == 'O') {
                    ++p;
                    phase = 0;
                }
                else {
                    p = 0;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
