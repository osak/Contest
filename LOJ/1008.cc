#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

ostream& ansout(int c) {
    return cout << "Case " << c << ": ";
}

int main() {
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    for(int CASE = 1; CASE <= T; ++CASE) {
        unsigned long long S;
        cin >> S;

        int root = (int)sqrt(S-1);
        int ord = S - (unsigned long long)root*root - 1;
        int row, col;
        if(root % 2 == 0) { //from right-bottom to left-top
            row = min(root+1, ord+1);
            col = (row<root+1) ? (root+1) : (root+1 - (ord-row+1));
        }
        else { //from left-top to right-bottom
            col = min(root+1, ord+1);
            row = (col<root+1) ? (root+1) : (root+1 - (ord-col+1));
        }

        ansout(CASE) << col << ' ' << row << endl;
    }

    return 0;
}
