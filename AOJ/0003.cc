#include <iostream>

using namespace std;

bool right(int a, int b, int c) {
    return a*a+b*b == c*c;
}

int main() {
    int n;
    cin >> n;
    while(n--) {
        int a, b, c;
        cin >> a >> b >> c;
        if(right(a,b,c) || right(a,c,b) || right(b,c,a)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
