//Name: Sum of Nth decimal places
//Level: 1
//Category: 数論,やるだけ
//Note:

/*
 * doubleに突っ込むだけだと有効桁数が足りないので、筆算していく
 */
#include <iostream>

using namespace std;

int main() {
    int a, b, n;
    while(cin >> a >> b >> n) {
        int sum = 0;
        a %= b;
        for(int i = 0; i < n; ++i) {
            a *= 10;
            sum += a / b;
            a %= b;
        }
        cout << sum << endl;
    }
    return 0;
}
