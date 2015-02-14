//Name: Frequency Distribution of Height
//Level: 1
//Category: やるだけ
//Note: 

/**
 */
#include <iostream>
#include <algorithm>

using namespace std;

bool solve(bool first) {
    int N;
    if(!(cin >> N)) return false;
    int cnt[6] = {0};

    for(int i = 0; i < N; ++i) {
        double d;
        cin >> d;
        d -= 165;
        if(d < 0) {
            cnt[0]++;
        } else {
            cnt[min(5, (int)d / 5 + 1)]++;
        }
    }
    for(int i = 0; i < 6; ++i) {
        cout << i+1 << ":";
        for(int j = 0; j < cnt[i]; ++j) {
            cout << "*";
        }
        cout << endl;
    }
    return true;
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
