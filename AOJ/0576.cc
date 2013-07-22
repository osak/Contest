//Name: Homework
//Level: 1
//Category: やるだけ
//Note:
#include <iostream>

using namespace std;

int main() {
    int L, A, B, C, D;
    cin >> L >> A >> B >> C >> D;
    const int a = (A / C) + ((A % C) != 0);
    const int b = (B / D) + ((B % D) != 0);
    cout << L - max(a, b) << endl;
    return 0;
}
