//Name: Matrix-like Computation
//Level: 1
//Category: やるだけ
//Note:

#include <iostream>
#include <vector>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<vector<int>> v(N+1, vector<int>(N+1, 0));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> v[i][j];
            v[i][N] += v[i][j];
            v[N][j] += v[i][j];
            v[N][N] += v[i][j];
        }
    }
    for(int i = 0; i < N+1; ++i) {
        for(int j = 0; j < N+1; ++j) {
            cout.width(5);
            cout << v[i][j];
        }
        cout << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    while(solve()) ;
    return 0;
}
