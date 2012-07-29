//Name: Plastic Board
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>

using namespace std;

int main() {
    int l1, l2, l3;
    char c1, c2;
    int rect = 0, diamond = 0;

    while(cin >> l1 >> c1 >> l2 >> c2 >> l3) {
        if(l1*l1+l2*l2 == l3*l3) ++rect;
        if(l1 == l2) ++diamond;
    }
    cout << rect << endl;
    cout << diamond << endl;

    return 0;
}
