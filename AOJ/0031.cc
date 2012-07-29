//Name: Weight
//Level: 1
//Category: 数論,やるだけ
//Note:

/*
 * 2進数に変換するだけ。
 */
#include <iostream>

using namespace std;

int main() {
    int N;
    while(cin >> N) {
        bool first = true;
        for(int i = 1; i <= N; i <<= 1) {
            if(N & i) {
                if(!first) cout << ' ';
                cout << i;
                first = false;
            }
        }
        cout << endl;
    }
    return 0;
}
