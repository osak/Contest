//Name: Exit Survey
//Level: 1
//Category: やるだけ
//Note: 

/**
 * がんばる。
 */
#include <iostream>

using namespace std;

bool solve(bool first) {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    long long sum = 0;
    for(int i = 0; i < N; ++i) {
        int v;
        cin >> v;
        sum += v;
    }
    cout << sum / N << endl;
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
