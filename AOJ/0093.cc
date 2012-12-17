//Name: Leap Year
//Level: 1
//Category: うるう年,やるだけ
//Note:

#include <iostream>

using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    bool first = true;
    while(true) {
        int a, b;
        cin >> a >> b;
        if(!a && !b) break;
        if(!first) cout << endl;
        bool found = false;
        for(int i = a; i <= b; ++i) {
            if(i % 4 == 0) {
                if(i % 400 == 0 || i % 100 != 0) {
                    cout << i << endl;
                    found = true;
                }
            }
        }
        if(!found) cout << "NA" << endl;
        first = false;
    }
    return 0;
}
