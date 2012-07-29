//Name: Sum and Average
//Level: 1
//Category: やるだけ
//Note

/*
 * 四捨五入にはround()を使う。
 */
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int v, n;
    char comma;
    int vsum = 0, nsum = 0;
    int cnt = 0;
    while(cin >> v >> comma >> n) {
        vsum += v*n;
        nsum += n;
        cnt++;
    }
    cout << vsum << endl;
    cout << round((double)nsum/cnt) << endl;
    return 0;
}
