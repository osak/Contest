#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;
    int h = 0;
    vector<bool> visited(N, false);
    for(int i = 1; i < 2*N; ++i) {
        visited[h] = true;
        h = (h+i) % N;
    }

    bool ok = true;
    for(int i = 0; i < N; ++i) {
        if(!visited[i]) {
            ok = false;
            break;
        }
    }

    cout << (ok?"YES":"NO") << endl;

    return 0;
}
