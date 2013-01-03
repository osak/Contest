#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> Column;
typedef vector<Column> Matrix;
const unsigned int MOD = 1000000007;

Matrix operator *(const Matrix &m, const Matrix &n) {
    Matrix res(m);
    const int R = (int)m.size();
    const int C = (int)n[0].size();
    const int N = (int)n.size();
    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            unsigned long long acc = 0;
            for(int k = 0; k < N; ++k) {
                acc += (unsigned long long)m[i][k] * n[k][j];
                acc %= MOD;
            }
            res[i][j] = (int)(acc % MOD);
        }
    }
    return res;
}

int modpow(int a, long long x) {
    if(x == 0) return 1;
    if(x == 1) return a;
    int half = modpow(a, x/2);
    int rem = (x%2==1) ? a : 1;
    unsigned long long v = ((unsigned long long)half * half) % MOD;
    v *= rem;
    return v % MOD;
}

ostream& operator <<(ostream &os, const Matrix &m) {
    for(int i = 0; i < m.size(); ++i) {
        for(int j = 0; j < m[i].size(); ++j) {
            os << m[i][j] << ' ';
        }
        os << endl;
    }
    return os;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    vector<Matrix> bases;
    Matrix org(3, Column(3));
    org[0][0] = org[0][1] = org[0][2] = org[1][0] = org[2][1] = 1;
    for(int i = 0; i < 50; ++i) {
        bases.push_back(org);
        //cout << org << endl;
        org = org * org;
    }
    Matrix identity(3, Column(3));
    identity[0][0] = identity[1][1] = identity[2][2] = 1;

    int T;
    cin >> T;
    while(T--) {
        long long N;
        cin >> N;
        
        Matrix m = identity;
        long long n = N-1;
        for(int i = 0; n > 0; ++i, n>>=1) {
            if(n&1) m = m * bases[i];
        }
        int pat = modpow(2, N);
        for(int r = 0; r < 3; ++r) {
            for(int c = 0; c < 2; ++c) {
                pat -= m[r][c];
                while(pat < 0) pat += MOD;
                pat %= MOD;
            }
        }
        cout << pat << endl;
    }

    return 0;
}
