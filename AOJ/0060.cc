//Name: Card Game
//Level: 1
//Category: 全探索,やるだけ
//Note:

#include <iostream>

using namespace std;

int main() {
    int c1, c2, c3;
    while(cin >> c1 >> c2 >> c3) {
        int cnt = 0;
        for(int i = 1; i <= 10; ++i) {
            if(i == c1 || i == c2 || i == c3) continue;
            if(c1+c2+i <= 20) ++cnt;
        }
        if(cnt >= 4) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
