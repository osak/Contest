//Name: Tic Tac Toe
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>
#include <string>

using namespace std;

#define CHECK(a,b,c) ((line[a]==line[b]) && (line[b]==line[c]) && (line[a] != 's') && (ans=line[a]))

int main() {
    string line;
    while(cin >> line) {
        char ans = 'd';
        CHECK(0,1,2); CHECK(3,4,5); CHECK(6,7,8);
        CHECK(0,3,6); CHECK(1,4,7); CHECK(2,5,8);
        CHECK(0,4,8); CHECK(2,4,6);
        cout << ans << endl;
    }
    return 0;
}
