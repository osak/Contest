// Accumulated sum of 2D matrix.
// O(RC) for freeze() and O(1) for get (operator ()).
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

// Used in:
// AOJ0098
