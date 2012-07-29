#include <iostream>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    while(K--) {
        int x, y;
        cin >> x >> y;
        if(x > (N+1)/2) x = N+1-x;
        if(y > (N+1)/2) y = N+1-y;
        if(y <= x) cout << ((y-1)%3)+1 << endl;
        else cout << ((x-1)%3)+1 << endl;
    }
    return 0;
}
