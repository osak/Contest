#include <iostream>

using namespace std;

int main() {
    while(true) {
        int n;
        cin >> n;
        if(!n) break;

        n = 1000-n;
        int cnt = 0;
        cnt += n/500;
        n %= 500;
        cnt += n/100;
        n %= 100;
        cnt += n/50;
        n %= 50;
        cnt += n/10;
        n %= 10;
        cnt += n/5;
        n %= 5;
        cnt += n;
        cout << cnt << endl;
    }
    return 0;
}
