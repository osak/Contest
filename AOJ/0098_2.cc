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

template<typename T>
struct Accumulate2D {
    vector<vector<T>> v;

    Accumulate2D(int R, int C) {
        v.resize(R, vector<T>(C));
    }

    void set(int r, int c, const T &val) {
        v[r][c] = val;
    }

    T& setter(int r, int c) {
        return v[r][c];
    }

    void freeze() {
        const int R = v.size();
        const int C = v[0].size();
        for(int r = 0; r < R; ++r) {
            for(int c = 0; c < C; ++c) {
                if(r > 0) v[r][c] += v[r-1][c];
                if(c > 0) v[r][c] += v[r][c-1];
                if(r > 0 && c > 0) v[r][c] -= v[r-1][c-1];
            }
        }
    }

    // Returns cumulative sum of ([r1, r2), [c1, c2))
    T operator ()(int r1, int c1, int r2, int c2) const {
        T res = v[r2-1][c2-1];
        if(r1 > 0) res -= v[r1-1][c2-1];
        if(c1 > 0) res -= v[r2-1][c1-1];
        if(r1 > 0 && c1 > 0) res += v[r1-1][c1-1];
        return res;
    }
};

bool solve() {
    int N;
    if(!(cin >> N)) return false;
    if(!N) return false;

    Accumulate2D<long long> acc(N, N);
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> acc.setter(i, j);
        }
    }
    acc.freeze();

    long long ans = -100000;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            for(int k = i+1; k <= N; ++k) {
                for(int l = j+1; l <= N; ++l) {
                    ans = max(ans, acc(i, j, k, l));
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
