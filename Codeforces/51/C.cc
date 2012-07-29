#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    bool win = false;
    for(int i = 0; i < K; ++i) {
        int px, py;
        cin >> px >> py;

        if(px-1 <= 4 || py-1 <= 4 || N-px <= 4 || M-py <= 4) {
            win = true;
            break;
        }
    }

    cout << (win?"YES":"NO") << endl;

    return 0;
}
