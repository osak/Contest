//Name: Data Conversion
//Level: 1
//Category: 文字列,やるだけ
//Note:

#include <iostream>
#include <vector>

using namespace std;

int main() {
    while(true) {
        int N;
        cin >> N;
        if(!N) break;

        char table[256];
        for(int i = 0; i < 256; ++i) {
            table[i] = i;
        }
        for(int i = 0; i < N; ++i) {
            char c, d;
            cin >> c >> d;
            table[c] = d;
        }
        int M;
        cin >> M;
        while(M--) {
            char c;
            cin >> c;
            cout << table[c];
        }
        cout << endl;
    }
    return 0;
}
