#include <iostream>

using namespace std;

int main() {
    while(true) {
        int a[4], b[4];
        for(int i = 0; i < 4; ++i) cin >> a[i];
        for(int i = 0; i < 4; ++i) cin >> b[i];
        if(cin.eof()) break;

        int hit = 0, blow = 0;
        for(int i = 0; i < 4; ++i) {
            if(a[i] == b[i]) {
                ++hit;
                a[i] = b[i] = -1;
            }
        }
        for(int i = 0; i < 4; ++i) {
            if(b[i] == -1) continue;
            for(int j = 0; j < 4; ++j) {
                if(a[j] == b[i]) {
                    ++blow;
                    a[j] = b[i] = -1;
                    break;
                }
            }
        }

        cout << hit << ' ' << blow << endl;
    }
    return 0;
}
