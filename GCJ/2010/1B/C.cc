#include <iostream>

using namespace std;

int N;

int combination(int n, int r) {
    int nn = 1;
    for(int i = 0; i < r; ++i) {
        nn *= (n-i);
    }
    for(int i = 2; i <= r; ++i) {
        nn /= i;
    }
    return nn;
}

int pattern(int prevpos, int prevnum, int pos) {
    int cnt = 0;
    for(int i = prevnum+(pos-prevpos); i < N; ++i) {
        cnt += pattern(pos, i, i) * combination(i-prevnum-1, (pos-prevpos-1));
    }
    //For N
    cnt += combination(N-prevnum-1, pos-prevpos-1);
    cout << prevpos << " " << pos << " " << cnt << endl;

    return cnt;
}

int main() {
    int cases;
    cin >> cases;

    for(int C = 1; C <= cases; ++C) {
        cin >> N;

        int cnt = 0;
        for(int i = 2; i < N; ++i) {
            cnt += pattern(1, i, i);
        }
        //For N
        cnt += 1;
        cout << "Case #" << C << ": " << cnt << endl;
    }
}
