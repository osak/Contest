//Name: 
//Level: 
//Category: 
//Note: 

/**
 *
 */
#include <iostream>
#include <vector>

using namespace std;

bool check(vector<vector<int>> &v) {
    const int N = v.size();
    for(int k = 0; k < N; ++k) {
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                if(v[i][j] == -1) {
                    if(v[i][k] != -1 && v[k][j] != -1) return false;
                } else {
                    if(v[i][k] != -1 && v[k][j] != -1 && v[i][j] > v[i][k] + v[k][j]) return false;
                }
            }
        }
    }
    return true;
}

bool solve() {
    int N;
    cin >> N;
    vector<vector<int>> v(N, vector<int>(N));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> v[i][j];
        }
    }
    for(int i = 0; i < N; ++i) {
        if(v[i][i] != 0) {
            cout << "NO" << endl;
            return true;
        }
    }

    if(check(v)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    int T;
    cin >> T;
    while(T-- && solve()) {
    }
    return 0;
}
