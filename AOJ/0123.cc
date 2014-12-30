//Name: Speed Skating Badge Test
//Level: 1
//Category: やるだけ
//Note: 

/**
 * 問題文の通りに処理する。
 *
 * オーダーは O(R)。
 * ただしRはランクの数。
 */
#include <iostream>

using namespace std;

bool solve() {
    double A, B;
    if(!(cin >> A >> B)) return false;

    string judge = "NA";
    if(A < 35.5 && B < 71.0) judge = "AAA";
    else if(A < 37.5 && B < 77.0) judge = "AA";
    else if(A < 40.0 && B < 83.0) judge = "A";
    else if(A < 43.0 && B < 89.0) judge = "B";
    else if(A < 50.0 && B < 105.0) judge = "C";
    else if(A < 55.0 && B < 116.0) judge = "D";
    else if(A < 70.0 && B < 148.0) judge = "E";
    cout << judge << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) ;
    return 0;
}
