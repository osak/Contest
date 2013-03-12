#include <iostream>

using namespace std;

int matrix[1000][1000];

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    int N;
    cin >> N;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> matrix[i][j];
        }
    }
    if(N == 2) {
        cout << "1 1" << endl;
    } else {
        int a0 = (matrix[0][1]-matrix[1][2]+matrix[0][2]) / 2;
        cout << a0;
        for(int i = 1; i < N; ++i) {
            cout << ' ' << matrix[0][i] - a0;
        }
        cout << endl;
    }
    return 0;
}
