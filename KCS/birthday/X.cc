#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    cin.tie(0);

    int N;
    cin >> N;
    srand(N);
    for(int i = 0; i < 20; ++i) {
        if(i > 0) cout << ' ';
        cout << rand() % 100;
    }
    cout << endl;
    return 0;
}
