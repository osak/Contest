#include <iostream>

using namespace std;

int main() {
    while(true) {
        int R, C;
        cin >> R >> C;
        if(!R && !C) break;

        if(R%2 == 1 && C%2 == 1) cout << "no" << endl;
        else cout << "yes" << endl;
    }
    return 0;
}
