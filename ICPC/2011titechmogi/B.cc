#include <iostream>
#include <cstring>

using namespace std;

int saw[1000001];

int main() {
    ios::sync_with_stdio(0);

    while(true) {
        int X, Y;
        cin >> X >> Y;
        if(!X && !Y) break;

        int pos = 0;
        int start = 0;
        int cur = X;
        memset(saw, -1, sizeof(saw));
        for(; saw[cur] == -1; ++pos) {
            saw[cur] = pos;
            if(cur == 0) break;
            cur *= 10;
            cur = cur % Y;
        }

        cout << saw[cur] << ' ' << pos-saw[cur] << endl;
    }
}
