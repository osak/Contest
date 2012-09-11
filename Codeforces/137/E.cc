//Name: Decoding Genome
//Level: 3
//Category: 数学,行列累乗
//Note: Codeforces #137

/*
 * 漸化式を行列表示して，累乗により求める．
 * abが禁止のときは行列の[b][a]要素が0になり，それ以外は1となる．
 * あとは指数の2進数展開を使ってこの行列のN-1乗を求めればよい．
 */
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

typedef unsigned long long ULL;
typedef vector<ULL> Row;
typedef vector<Row> Matrix;

const ULL MOD = 1000000007;

int c2i(char c) {
    if(islower(c)) return c-'a';
    if(isupper(c)) return c-'A'+26;
    return 0;
}

Matrix& operator*=(Matrix &a, const Matrix &b) {
    const int size = a.size();
    Matrix res(a);
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            ULL acc = 0;
            for(int k = 0; k < size; ++k) {
                acc += a[i][k] * b[k][j];
                acc %= MOD;
            }
            res[i][j] = acc;
        }
    }
    a = res;
    return a;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    ULL N, M, K;
    cin >> N >> M >> K;
    Matrix mat(M, Row(M, 1));
    for(int i = 0; i < K; ++i) {
        string str;
        cin >> str;
        const int col = c2i(str[0]), row = c2i(str[1]);
        if(row < M && col < M) mat[row][col] = 0;
    }
    vector<Matrix> base;
    for(int i = 1; i < 64; ++i) {
        base.push_back(mat);
        mat *= mat;
    }

    Matrix need(M, Row(M, 0));
    for(int i = 0; i < M; ++i) need[i][i] = 1;
    ULL tmp = N-1;
    for(int bit = 0; tmp > 0; ++bit, tmp>>=1) {
        if(tmp & 1) {
            need *= base[bit];
        }
    }
    ULL ans = 0;
    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < M; ++j) {
            ans += need[i][j];
            ans %= MOD;
        }
    }
    cout << ans << endl;
    return 0;
}
