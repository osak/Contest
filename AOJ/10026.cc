//Name: Standard Deviation
//Level: 1
//Category: やるだけ
//Note:

/**
 * 式のとおりに実装するだけ。
 *
 * オーダーは O(N)。
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <cmath>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<int> v(N);
    for(int i = 0; i < N; ++i) {
        cin >> v[i];
    }
    const double avg = accumulate(begin(v), end(v), 0.0) / N;
    const double var = accumulate(begin(v), end(v), 0.0, [avg](double acc, double d) {
            return acc + pow(d - avg, 2);
            }) / N;
    cout << sqrt(var) << endl;
    return true;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    while(solve()) ;
    return 0;
}
