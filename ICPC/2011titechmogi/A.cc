#include <iostream>
#include <algorithm>
using namespace std;

int key(int n)
{
    int s = 0;
    int m = 1;
    for (int i = 2; i <= n; i++) {
        if (n % i == 0) {
            s += i;
            m = max(m, i);
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    return m - (s-m);
}

int main()
{
    int a, b;
    while (cin >> a >> b && a != 0) {
        int x = key(a);
        int y = key(b);
        cout << (x <= y ? "b" : "a") << endl;
    }
    return 0;
}
