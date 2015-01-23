//Name: Maximum Sum Sequence II
//Level: 2
//Category: データ構造,累積和
//Note:

/**
 * 行列要素の累積和を求めておけば、任意の矩形に対して和をO(1)で計算できる。
 *
 * オーダーは O(N^4)。
 */
#include <iostream>
#include <vector>

using namespace std;

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    vector<vector<long long>> v(N, vector<long long>(N));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> v[i][j];
        }
    }
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if(i > 0) v[i][j] += v[i-1][j];
            if(j > 0) v[i][j] += v[i][j-1];
            if(i > 0 && j > 0) v[i][j] -= v[i-1][j-1];
        }
    }
    long long ans = -100000;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            for(int k = i; k < N; ++k) {
                for(int l = j; l < N; ++l) {
                    long long sum = v[k][l];
                    if(i > 0) sum -= v[i-1][l];
                    if(j > 0) sum -= v[k][j-1];
                    if(i > 0 && j > 0) sum += v[i-1][j-1];
                    ans = max(ans, sum);
                }
            }
        }
    }
    cout << ans << endl;
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
