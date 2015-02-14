//Name: Rotation of a Pattern
//Level: 2
//Category: シミュレーション
//Note: 

/**
 * がんばる。
 */
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int S = 8;
void rotate(vector<string> &v) {
    for(int r = 0; r < S/2; ++r) {
        for(int c = 0; c < S/2; ++c) {
            const char tmp = v[r][c];
            v[r][c] = v[S-c-1][r];
            v[S-c-1][r] = v[S-r-1][S-c-1];
            v[S-r-1][S-c-1] = v[c][S-r-1];
            v[c][S-r-1] = tmp;
        }
    }
}

template<typename T>
ostream& operator <<(ostream &os, const vector<T> &v) {
    for(const T &t : v) {
        os << t << endl;
    }
    return os;
}

bool solve(bool first) {
    vector<string> v(S);
    for(int i = 0; i < S; ++i) {
        cin >> v[i];
    }
    for(int r = 90; r <= 270; r += 90) {
        cout << r << endl;
        rotate(v);
        cout << v;
    }
    return false;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    bool first = true;
    while(solve(first)) {
        first = false;
    }
    return 0;
}
