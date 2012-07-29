#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    vector<int> val(M, INT_MAX);

    while(N--) {
        int r,c;
        cin >> r >> c;
        --r;
        val[r] = min(val[r], c);
    }
    int total = 0;
    for(int i = 0; i < M; ++i) {
        total += val[i];
    }

    cout << min(total, K) << endl;
    return 0;
}
